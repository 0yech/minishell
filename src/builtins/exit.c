/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:36:24 by estettle          #+#    #+#             */
/*   Updated: 2025/02/25 12:36:39 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token **token_list)
{
	int	exit_status;

	if (token_list && ((*token_list)->next && (*token_list)->next->value))
	{
		exit_status = ft_atoi((*token_list)->next->value);
		if (exit_status > 255 || exit_status < -256)
			exit_status = exit_status % 256;
	}
	else
		exit_status = 0;
	tokens_clear(token_list);
	rl_clear_history();
	env_clear(env_get());
	exit(exit_status);
}
