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
 * @brief Safe close syscall.
 * Closes a fd and sets it to -1 to express it is closed.
 * Does not close the fd if it is negative.
 *
 * @note Make sure to call perror when xclose returns -1!
 * @return 0 if everything went well, 1 if the pointer is NULL or the fd is
 * negative (invalid), -1 if close failed.
 */
int	xclose(int *fd)
{
	int	return_value;

	if (!fd || *fd < 0)
		return (1);
	return_value = close(*fd);
	*fd = -1;
	return (return_value);
}

/**
 * @brief Resets STDIN and STDOUT to their standard file descriptors.
 * @param cmd The command containing the stdin and stdout copies.
 */
void	redirect_dupes(t_command *cmd)
{
	if (dup2(cmd->fdio->stdincpy, STDIN_FILENO) == -1)
		perror("minishell (redirect_dupes) - dup2 (in)");
	if (dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO) == -1)
		perror("minishell (redirect_dupes) - dup2 (out)");
}

/**
 * @brief Copies stdin and stdout into a command.
 *
 * @param cmd The command to store the standard fds in.
 * @return 0 if everything went fine, -1 if an error occur
 */
void	fill_dupes(t_command *cmd)
{
	cmd->fdio->stdincpy = dup(STDIN_FILENO);
	if (cmd->fdio->stdincpy == -1)
		perror("minishell (fill_dupes) - dup (in)");
	cmd->fdio->stdoutcpy = dup(STDOUT_FILENO);
	if (cmd->fdio->stdoutcpy == -1)
		perror("minishell (fill_dupes) - dup (out)");
}
