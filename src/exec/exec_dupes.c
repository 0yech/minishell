/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dupes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 06:14:25 by nrey              #+#    #+#             */
/*   Updated: 2025/04/27 07:06:17 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_dupes(t_command *cmd)
{
	if (dup2(cmd->fdio->stdincpy, STDIN_FILENO) == -1)
		return (perror("minishell (execute_piped_commands) - dup2 (in)"), -1);
	if (dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO) == -1)
		return (perror("minishell (execute_piped_commands) - dup2 (out)"), -1);
	return (0);
}

int	fill_dupes(t_command *cmd)
{
	cmd->fdio->stdincpy = dup(STDIN_FILENO);
	if (cmd->fdio->stdincpy == -1)
		return (perror("minishell (execute_piped_commands) - dup (in)"), -1);
	cmd->fdio->stdoutcpy = dup(STDOUT_FILENO);
	if (cmd->fdio->stdoutcpy == -1)
		return (perror("minishell (execute_piped_commands) - dup (out)"), -1);
	return (0);
}
