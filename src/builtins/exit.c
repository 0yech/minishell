/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:36:24 by estettle          #+#    #+#             */
/*   Updated: 2025/01/22 20:26:32 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token **token_list)
{
	int	exit_status;

	if ((*token_list)->next && (*token_list)->next->value)
	{
		exit_status = ft_atoi((*token_list)->next->value);
		if (exit_status > 255 || exit_status < -256)
			exit_status = exit_status % 256;
	}
	else
		exit_status = 0;
	tokens_clear(token_list);
	exit(exit_status);
}
