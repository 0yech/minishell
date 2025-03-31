/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:08 by estettle          #+#    #+#             */
/*   Updated: 2025/03/27 19:32:01 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : make this return an int
/**
 * @brief Loops over a token list and a freshly created command list and fills
 * the latter with information contained in the token.
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
		}
		token = token->next;
	}
}

/**
* @brief Takes a token as argument and counts the number of options and
* arguments contained within, then returns it.
*
* @details Starts at 1 to include the command name as well.
*/
int	count_argsopt(t_token *token)
{
	int	count;

	count = 1;
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION || token->type == ARGUMENT)
			count++;
		token = token->next;
	}
	return (count);
}

char	**args_to_argv(t_token *arg)
{
	size_t	i;
	char	**argv;

	argv = ft_calloc(count_argsopt(arg) + 1, sizeof(char *));
	if (!argv)
		return (perror("minishell (args_to_argv) - malloc"), NULL);
	i = 0;
	while (arg && arg->type != PIPE)
	{
		if (i == 0 || arg->type == OPTION || arg->type == ARGUMENT)
		{
			argv[i] = ft_strdup(arg->value);
			if (!argv[i])
			{
				perror("minishell (extract_args) - ft_strdup");
				while (i > 0)
					free(argv[--i]);
				return (free(argv), NULL);
			}
			i++;
		}
		arg = arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * @brief Extracts arguments and options from a given token.
 *
 * @param token The token to analyze.
 * @return A double char pointer containing a string for each argument / option.
 */
t_token	**extract_args(t_token *token)
{
	int		i;
	t_token	*tmp;
	t_token	**args;

	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
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
