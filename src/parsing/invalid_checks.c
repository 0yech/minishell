/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:31:29 by nrey              #+#    #+#             */
/*   Updated: 2025/04/05 17:10:46 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_after_pipe_invalid(t_token_type type)
{
	return (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
			|| type == APPEND || type == HEREDOC);
}

int	valid_pipes(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || is_token_after_pipe_invalid(token->next->type))
				write(STDERR_FILENO, "syntax error near unexpected token `|'\n", 39);
			else
			{
				token = token->next;
				continue ;
			}
			env_set_key("?", "2");
			return (1);
		}
		if ((token->type == REDIRECT_IN || token->type == REDIRECT_OUT
			|| token->type == APPEND || token->type == HEREDOC)
		   && (!token->next || token->next->type != REDIRECT_FILE))
	   	{	
		   write(STDERR_FILENO, "syntax error near unexpected token `newline'\n", 46);
		   env_set_key("?", "2");
		   return (1);
	   	}
		token = token->next;
	}
	return (0);
}
