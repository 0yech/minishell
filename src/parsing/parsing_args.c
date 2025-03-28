/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:08 by estettle          #+#    #+#             */
/*   Updated: 2025/03/28 12:08:31 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : make this return an int
/**
 * @brief Loops over a token list and a freshly created command list and fills
 * the latter with information contained in the tokens about redirections and fds.
 *
 * @param cmd A pointer to the first element of the command list.
 * @param token A pointer to the first element of the token list.
 */
void	fill_args_fds(t_command *cmd, t_token *token)
{
	t_command	*current;

	current = cmd;
	while (token)
	{
		if (token->type == PIPE)
		{
			if (current == NULL || current->next == NULL)
				return ;
			current = current->next;
		}
		else if (current && current->fdio)
		{
			if (token->type == REDIRECT_IN && token->next
				&& token->next->type == REDIRECT_FILE)
			{
				current->fdio->input = ft_strdup(token->next->value);
				if (!current->fdio->input)
					perror("minishell (fill_args_fds) - ft_strdup");
			}
			else if (token->type == REDIRECT_OUT && token->next
				&& token->next->type == REDIRECT_FILE)
			{
				current->fdio->outtype = RED_OUT;
				current->fdio->output = ft_strdup(token->next->value);
				if (!current->fdio->output)
					perror("minishell (fill_args_fds) - ft_strdup");
			}
			else if (token->type == APPEND && token->next
				&& token->next->type == REDIRECT_FILE)
			{
				current->fdio->outtype = APD;
				current->fdio->output = ft_strdup(token->next->value);
				if (!current->fdio->output)
					perror("minishell (fill_args_fds) - ft_strdup");
				current->fdio->fdout = O_WRONLY | O_CREAT | O_APPEND;
			}
			else if (token->type == HEREDOC && token->next
				&& token->next->type == DELIM)
			{
				current->fdio->hd_delim = ft_strdup(token->next->value);
				if (!current->fdio->hd_delim)
					perror("minishell (fill_args_fds) - ft_strdup");
			}
		}
		token = token->next;
	}
}

/**
* @brief Takes a token as argument and counts the number of options and
* arguments contained within (necessary for argv), then returns it.
*/
size_t	count_argv(t_token *token)
{
	size_t	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION || token->type == ARGUMENT)
			count++;
		token = token->next;
	}
	return (count);
}

/**
 * @brief Creates a double char pointer with all arguments from a command, ready
 * to be passed to execve().
 */
char	**tokens_to_argv(t_token **args)
{
	char	**argv;
	size_t	i;

	argv = ft_calloc(count_argv(*args), sizeof(char *));
	if (!argv)
		return (perror("minishell (tokens_to_argv) - malloc"), NULL);
	i = 0;
	while (*args)
	{
		if ((*args)->type == OPTION || (*args)->type == ARGUMENT)
		{
			argv[i] = ft_strdup((*args)->value);
			if (!argv[i++])
			{
				while (i--)
					free(argv[i]);
				return (perror("minishell (tokens_to_argv) - malloc"), NULL);
			}
		}
		args++;
	}
	return (argv);
}

/**
 * @brief Extracts arguments and options from the lexing tokens.
 *
 * @param token The first element of the list of tokens to analyze.
 * @return A double char pointer containing a string for each argument / option.
 */
t_token **extract_args(t_token* token)
{
	size_t	i;
	t_token	*tmp;
	t_token	**args;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	args = ft_calloc(i + 1, sizeof(t_token *));
	if (!args)
		return (perror("minishell (extract_args) - malloc"), NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		// TODO: idea : put the tokens themselves into the args, heredocs and normal arguments and options.
		// Then the heredoc handler will take care of taking out the delimiters and processing
		// This is probably necessary so we can not only have null commands with a heredoc,
		// but also multiple heredocs in sequence (ls << EOF << EOF << EOF)
		// It could even help to do the << 'EOF' part directly that way
		// I'll need a function that parses all tokens from a specific command in a list of arguments for argv
		args[i] = token;
		i++;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}
