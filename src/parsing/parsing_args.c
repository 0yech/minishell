/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:08 by estettle          #+#    #+#             */
/*   Updated: 2025/03/26 13:08:25 by estettle         ###   ########.fr       */
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
* arguments contained within, then returns it.
*/
int	count_argsopt(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE) // TODO Or redirections? Why stop only at pipes?
	{
		if (token->type == OPTION || token->type == ARGUMENT)
			count++;
		token = token->next;
	}
	return (count);
}

/**
 * @brief Extracts arguments and options from a given token.
 *
 * @param token The token to analyze.
 * @return A double char pointer containing a string for each argument / option.
 */
char	**extract_args(t_token *token)
{
	int		count;
	int		i;
	char	**args;

	i = 0;
	count = count_argsopt(token);
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (perror("minishell (extract_args) - malloc"), NULL);
	args[i] = ft_strdup(token->value);
	if (!args[i++])
		return (perror("minishell (extract_args) - ft_strdup"), free(args), NULL);
	token = token->next;
	while (token && token->type != PIPE) // TODO Or redirections? Why stop only at pipes?
	{
		if (token->type == OPTION || token->type == ARGUMENT)
		{
			args[i] = ft_strdup(token->value);
			if (!args[i])
			{
				perror("minishell (extract_args) - ft_strdup");
				while (i > 0)
					free(args[--i]);
				return (free(args), NULL);
			}
			i++;
		}
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}
