/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@protonmail    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:31:29 by nrey              #+#    #+#             */
/*   Updated: 2025/04/07 15:13:05 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : "<< > o" OR "<< >" should print new error syntax

bool	is_token_after_pipe_invalid(t_token_type type)
{
	return (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
			|| type == APPEND || type == HEREDOC);
}

int	is_valid_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || is_token_after_pipe_invalid(token->next->type))
		{
			write(STDERR_FILENO, "syntax error near unexpected token `|'\n", 39);
			return (-1);
		}
	}
	return (0);
}

int	is_valid_redirection(t_token *token)
{
	if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == APPEND || token->type == HEREDOC)
	{
		if (!token->next)
		{
			write(STDERR_FILENO, "syntax error near unexpected token `newline'\n", 45);
			return (-1);
		}
		else if ((token->type != HEREDOC && token->next->type != REDIRECT_FILE)
			|| (token->type == HEREDOC && token->next->type != DELIM))
		{
			write(STDERR_FILENO, "syntax error near unexpected token `", 37);
			write(STDERR_FILENO, token->next->value, ft_strlen(token->next->value));
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
