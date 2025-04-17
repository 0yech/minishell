/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:39:04 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/16 20:52:02 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the current command is a minishell builtin.
 *
 * @return 1 if the command is a builtin, 0 otherwise.
 */
int	is_builtin(t_command *current)
{
	if (!current || !current->command)
		return (0);
	if (ft_strncmp(current->command, "cd", 3) == 0
		|| ft_strncmp(current->command, "pwd", 4) == 0
		|| ft_strncmp(current->command, "env", 4) == 0
		|| ft_strncmp(current->command, "export", 7) == 0
		|| ft_strncmp(current->command, "unset", 6) == 0
		|| ft_strncmp(current->command, "pwd", 4) == 0
		|| ft_strncmp(current->command, "echo", 5) == 0
		|| ft_strncmp(current->command, "exit", 5) == 0)
		return (1);
	return (0);
}

/**
 * @brief Calls the appropriate builtin according to the name of the command
 * given as an argument and returns its exit status.
 * If the command isn't a builtin, -1 is returned.
 */
static int	exec_builtin(t_command *current)
{
	if (!current->next)
		close_child(current);
	if (ft_strncmp(current->command, "cd", 3) == 0)
		return (ft_cd(current));
	if (ft_strncmp(current->command, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(current->command, "env", 4) == 0)
		return (ft_env());
	if (ft_strncmp(current->command, "export", 7) == 0)
		return (ft_export(current));
	if (ft_strncmp(current->command, "unset", 6) == 0)
	{
		if (!current->argv[1])
			return (printf("unset : not enough arguments\n"), -1);
		return (ft_unset(current->argv[1]));
	}
	if (ft_strncmp(current->command, "echo", 5) == 0)
		return (ft_echo(current));
	if (ft_strncmp(current->command, "exit", 5) == 0)
		ft_exit(current);
	return (-1);
}

/**
 * @brief Checks if a command is a builtin, and if yes, executes the builtin.
 *
 * @param current The command to execute as a builtin.
 * @return The exit value of the builtin if the command was indeed one,
 * -1 if not or if an error occurred.
 */
int	exec_pipe_builtin(t_command *current)
{
	int	*stat_loc;
	int	exit_status;
	int	pid;

	if (current && current->command && current->next)
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell (exec_pipe_builtin) - fork"), 1);
		if (pid == 0)
		{
			close_child(current);
			exit_status = exec_builtin(current);
		}
		if (close(current->fdio->fdout) == -1)
			perror("minishell (exec_pipe_builtin) - close");
		if (pid == 0)
			exit(exit_status);
		stat_loc = ft_calloc(1, sizeof(int));
		if (!stat_loc)
			return (perror("minishell (exec_pipe_builtin) - malloc"), -1);
		if (wait(stat_loc) == -1)
			perror("minishell (exec_pipe_builtin) - wait");
		exit_status = WEXITSTATUS(*stat_loc);
		return (free(stat_loc), exit_status);
	}
	return (exec_builtin(current));
}
