/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:36:24 by estettle          #+#    #+#             */
/*   Updated: 2025/03/07 10:03:05 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_command *cmd)
{
	int	exit_status;

	if (cmd && (cmd->command && cmd->argv[1]))
	{
		exit_status = ft_atoi(cmd->argv[1]);
		if (exit_status > 255 || exit_status < -256)
			exit_status = exit_status % 256;
	}
	else
		exit_status = 0;
	free_command_list(cmd);
	rl_clear_history();
	env_clear(env_get());
	exit(exit_status);
}
