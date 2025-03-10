/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:08 by estettle          #+#    #+#             */
/*   Updated: 2025/03/10 11:41:25 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				&& token->next->type == REDIRECT_FILE) // <
				current->fdio->input = ft_strdup(token->next->value);
			else if (token->type == REDIRECT_OUT && token->next
				&& token->next->type == REDIRECT_FILE) // >
			{
				current->fdio->outtype = RED_OUT;
				current->fdio->output = ft_strdup(token->next->value);
			}
			else if (token->type == APPEND && token->next
				&& token->next->type == REDIRECT_FILE) // >>
			{
				current->fdio->outtype = APD;
				current->fdio->output = ft_strdup(token->next->value); // TODO noticed this leaked
				current->fdio->fdout = O_WRONLY | O_CREAT | O_APPEND;
			}
			else if (token->type == HEREDOC && token->next
				&& token->next->type == DELIM)
				current->fdio->hd_delim = ft_strdup(token->next->value);
		}
		token = token->next;
	}
}

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

char	**extract_args(t_token *token)
{
	int		count;
	int		i;
	char	**args;

	i = 0;
	count = count_argsopt(token);
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (free(args), NULL);
	args[i++] = ft_strdup(token->value);
	token = token->next;
	while (token && token->type != PIPE) // TODO Or redirections? Why stop only at pipes?
	{
		if (token->type == OPTION || token->type == ARGUMENT)
		{
			args[i] = ft_strdup(token->value);
			if (!args[i])
			{
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
