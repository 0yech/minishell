/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_update_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:56:33 by nrey              #+#    #+#             */
/*   Updated: 2025/04/27 15:58:15 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates the environment after attempting to execute a command.
 * 
 * @details Updates the ? variable with the exit_status.
 * 
 * @param exit_status The exit status returned by the command.
 * @return 0 if all went well, -1 otherwise.
 */
int	exec_update_env(int exit_status)
{
	char	*str_exit_status;

	str_exit_status = ft_itoa(exit_status);
	if (!str_exit_status)
		return (perror("minishell (exec_update_env) - malloc"), -1);
	if (env_set_key("?", str_exit_status) == 1)
		return (free(str_exit_status), -1);
	free(str_exit_status);
	return (0);
}
