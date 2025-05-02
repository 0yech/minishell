/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:36:24 by fireinside        #+#    #+#             */
/*   Updated: 2025/03/07 10:03:05 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_status(t_command *cmd, int exit_code)
{
	int	exit_status;
	int	i;

	if (cmd && cmd->command && cmd->argv[1])
	{
		i = 0;
		exit_status = ft_atoi(cmd->argv[1]);
		if (exit_status > 255 || exit_status < -256)
			exit_status = exit_status % 256;
		while (cmd->argv[1][i])
		{
			if (ft_isalpha(cmd->argv[1][i++]) == 1)
			{
				write(STDERR_FILENO,
					"minishell: exit: wow: numeric argument required\n", 48);
				return (2);
			}
		}
	}
	else
		exit_status = exit_code;
	return (exit_status);
}

int	ft_exit(t_command *cmd, int exit_code)
{
	int	exit_status;

	if (cmd && cmd->command && cmd->argv[1] && cmd->argv[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit_status = get_exit_status(cmd, exit_code);
	clear_data();
	rl_clear_history();
	env_clear(env_get());
	exit(exit_status);
}
