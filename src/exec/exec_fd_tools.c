/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:07:00 by nrey              #+#    #+#             */
/*   Updated: 2025/04/27 16:53:23 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

/**
 * @brief Closes the standard output and input copies inside a given command
 * struct.
 */
void	close_std_copies(t_command *cmd)
{
	if (cmd->fdio->stdincpy > STDERR_FILENO
		&& xclose(&cmd->fdio->stdincpy) == -1)
		perror("minishell (close_std_copies) - close (in)");
	if (cmd->fdio->stdoutcpy > STDERR_FILENO
		&& xclose(&cmd->fdio->stdoutcpy) == -1)
		perror("minishell (close_std_copies) - close (out)");
}

/**
 * @brief Closes all fdin and fdout in a command list if they aren't part of
 * the three standard file descriptors.
 * @param cmd_list A pointer to the head of the command list to go through.
 */
void	close_all_fds(t_command *cmd_list)
{
	t_command	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->fdio->fdin > STDERR_FILENO && xclose(&tmp->fdio->fdin) == -1)
			perror("minishell (close_all_fds) - close (in)");
		if (tmp->fdio->fdout > STDERR_FILENO && xclose(&tmp->fdio->fdout) == -1)
			perror("minishell (close_all_fds) - close (in)");
		tmp = tmp->next;
	}
}

/**
 * @brief Called by child processes to close all fds that aren't the ones related
 * to the command the child is tasked to run.
 *
 * @param cmd_list The head of the command list.
 * @param current_cmd The command the child is tasked to execute.
 */
void	close_all_other_fds(t_command *cmd_list, t_command *current_cmd)
{
	t_command	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		close_std_copies(tmp);
		if (tmp != current_cmd)
		{
			if (tmp->fdio->fdin != STDIN_FILENO
				&& tmp->fdio->fdin > STDERR_FILENO)
			{
				if (xclose(&tmp->fdio->fdin) == -1)
					perror("minishell (close_all_other_fds) - close (out)");
				tmp->fdio->fdin = STDIN_FILENO;
			}
			if (tmp->fdio->fdout != STDOUT_FILENO
				&& tmp->fdio->fdout > STDERR_FILENO)
			{
				if (xclose(&tmp->fdio->fdout) == -1)
					perror("minishell (close_all_other_fds) - close (in)");
				tmp->fdio->fdout = STDOUT_FILENO;
			}
		}
		tmp = tmp->next;
	}
}
