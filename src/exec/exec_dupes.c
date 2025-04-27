/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dupes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 06:14:25 by nrey              #+#    #+#             */
/*   Updated: 2025/04/27 16:49:08 by nrey             ###   ########.fr       */
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

void	child_fdio_redirections(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO && current->fdio->fdin != -1)
	{
		dup2(current->fdio->fdin, STDIN_FILENO);
		close(current->fdio->fdin);
	}
	if (current->fdio->fdout != STDOUT_FILENO && current->fdio->fdout != -1)
	{
		dup2(current->fdio->fdout, STDOUT_FILENO);
		close(current->fdio->fdout);
	}
}
