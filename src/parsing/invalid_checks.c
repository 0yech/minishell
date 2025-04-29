/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:31:29 by nrey              #+#    #+#             */
/*   Updated: 2025/04/14 17:32:15 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || token->next->type == PIPE)
		{
			write(STDERR_FILENO,
				"syntax error near unexpected token `|'\n", 39);
			return (-1);
		}
	}
	return (0);
}

static int	is_valid_redirection(t_token *token)
{
	if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == APPEND || token->type == HEREDOC)
	{
		if (!token->next)
		{
			write(STDERR_FILENO,
				"syntax error near unexpected token `newline'\n", 45);
			return (-1);
		}
		else if ((token->type != HEREDOC && token->next->type != REDIRECT_FILE)
			|| (token->type == HEREDOC && token->next->type != DELIM))
		{
			token = token->next;
			write(STDERR_FILENO, "syntax error near unexpected token `", 37);
			write(STDERR_FILENO, token->value, ft_strlen(token->value));
			write(STDERR_FILENO, "'\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	valid_pipes(t_token *token)
{
	if (token->prev == NULL && token->type == PIPE)
	{
		write(STDERR_FILENO,
			"syntax error near unexpected token `|'\n", 39);
		env_set_key("?", "2");
		return (1);
	}
	while (token)
	{
		if (is_valid_pipe(token) != 0 || is_valid_redirection(token) != 0)
		{
			env_set_key("?", "2");
			return (1);
		}
		token = token->next;
	}
	return (0);
}
