/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:31:29 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 23:13:20 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO - "|ls" shouldn't be valid. First token can't be a pipe. (syntax err)

static bool	is_token_after_pipe_invalid(t_token_type type)
{
	return (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC);
}

static int	is_valid_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || is_token_after_pipe_invalid(token->next->type))
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
