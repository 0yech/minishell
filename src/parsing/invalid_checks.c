/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:31:29 by nrey              #+#    #+#             */
/*   Updated: 2025/04/05 03:55:43 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_pipes(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE
			&& (!token->next || token->next->type == ARGUMENT
				|| token->next->type == PIPE || token->next->type == OPTION))
		{
			// can't update exit status without an existing command ?
			//exec_update_env(NULL, 2);   unexpected token must return code 2
			write(STDERR_FILENO, "syntax error near unexpected token `|'\n", 39);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
