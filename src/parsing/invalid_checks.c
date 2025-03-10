/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:31:29 by nrey              #+#    #+#             */
/*   Updated: 2025/03/10 09:04:34 by estettle         ###   ########.fr       */
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
			printf("Invalid or Double pipe detected - invalid_checks.c\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}
