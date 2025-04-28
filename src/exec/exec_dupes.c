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

/**
 * @brief Resets STDIN and STDOUT to their standard file descriptors.
 * @param cmd The command containing the stdin and stdout copies.
 */
void redirect_dupes(t_command* cmd)
{
	if (dup2(cmd->fdio->stdincpy, STDIN_FILENO) == -1)
		perror("minishell (execute_piped_commands) - dup2 (in)");
	if (dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO) == -1)
		perror("minishell (execute_piped_commands) - dup2 (out)");
}

/**
 * @brief Copies stdin and stdout into a command.
 *
 * @param cmd The command to store the standard fds in.
 * @return 0 if everything went fine, -1 if an error occur
 */
void fill_dupes(t_command* cmd)
{
	cmd->fdio->stdincpy = dup(STDIN_FILENO);
	if (cmd->fdio->stdincpy == -1)
		perror("minishell (execute_piped_commands) - dup (in)");
	cmd->fdio->stdoutcpy = dup(STDOUT_FILENO);
	if (cmd->fdio->stdoutcpy == -1)
		perror("minishell (execute_piped_commands) - dup (out)");
}

/**
 *
 * @param current
 */
void	child_fdio_redirections(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO && current->fdio->fdin != -1)
	{
		if (dup2(current->fdio->fdin, STDIN_FILENO) == -1)
			perror("minishell (child_fdio_redirections) - dup2 (in)");
		if (close(current->fdio->fdin) == -1)
			perror("minishell (child_fdio_redirections) - close (in)");
	}
	if (current->fdio->fdout != STDOUT_FILENO && current->fdio->fdout != -1)
	{
		if (dup2(current->fdio->fdout, STDOUT_FILENO) == -1)
			perror("minishell (child_fdio_redirections) - dup2 (out)");
		if (close(current->fdio->fdout) == -1)
			perror("minishell (child_fdio_redirections) - close (out)");
	}
}
