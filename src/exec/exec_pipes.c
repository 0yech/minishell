/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:21:22 by nrey              #+#    #+#             */
/*   Updated: 2025/03/27 10:14:09 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_PID 1024

/**
 * @brief Executes a command as a child process.
 * In case of error with execve, exits the child with 126.
 */
static void	exec_child(t_command *current)
{
	char	**envtab;
	char	*path;

	envtab = env_to_char(*env_get());
	if (!envtab)
	{
		clear_data();
		exit(126);
	}
	close_child(current);
	path = find_executable_path(current->command);
	if (!path)
	{
		free_array(envtab);
		clear_data();
		exit(126);
	}
	execve(path, current->argv, envtab);
	perror("minishell (exec_child) - execve");
	close_std_copies(current);
	free(path);
	free_array(envtab);
	env_clear(env_get());
	clear_data();
	exit(126);
}

/**
 * @brief Executes a command as a child process (only if a pipe is present
 * in the form of multiple commands and redirects its output to
 * the appropriate file descriptor.
 *
 * @param current The command to execute.
 * @return 0 if all went well, -1 otherwise.
 */
static int	process_command(t_command *current)
{
	pid_t		pid;
	int			status;

	ignore_sig(SIGINT);
	pid = fork();
	if (pid == -1)
		return (perror("minishell (process_command) - fork"), -1);
	if (pid == 0)
	{
		default_sig(SIGINT);
		default_sig(SIGQUIT);
		if (is_builtin(current))
		{
			close_child(current);
			status = exec_builtin(current);
			env_clear(env_get());
			close_std_copies(current);
			clear_data();
			exit(status);
		}
		exec_child(current);
	}
	else if (pid > 0)
		close_parent(current);
	return (pid);
}

// TODO (optional): Pipelines should return the exit status of the rightmost command
// that failed, or 0 if all commands exited with 0.
// We could loop over the commands and as we waitpid them, only update the
// exit status to 0 if no error was found before
static void	wait_for_exec(t_command *cmd, pid_t pids[MAX_PID], int index)
{
	int			i;
	int			status;
	t_command	*tmp;

	i = 0;
	status = 0;
	tmp = cmd;
	while (i < index)
	{
		if (waitpid(pids[i], &status, 0) == -1 && errno != EINTR)
			perror("minishell (wait_for_exec) - waitpid");
		exec_update_env(WEXITSTATUS(status));
		i++;
	}
	while (tmp)
	{
		close_parent(tmp);
		tmp = tmp->next;
	}
}

static int	parallel_exec(t_command *current, pid_t pids[MAX_PID])
{
	int	i;

	i = 0;
	while (current)
	{
		setup_io(current, current->arguments);
		if (current->isvalid == true && current->command && current->command[0])
		{
			pids[i] = process_command(current);
			if (pids[i] != -1)
				i++;
		}
		else if (!current->isvalid)
			print_exec_checks(current, current->exec_code);
		current = current->next;
	}
	return (i);
}

/**
 * @brief Executes a command as a child process and redirects its output to
 * the appropriate file descriptor.
 *
 * @param cmd The command to execute.
 * @return 0 if all went well, -1 otherwise.
 */
int	execute_piped_commands(t_command *cmd)
{
	pid_t		pids[MAX_PID];

	if (!cmd)
		return (-1);
	if (!cmd->next && is_builtin(cmd))
	{
		setup_io(cmd, cmd->arguments);
		exec_update_env(exec_builtin(cmd));
		redirect_dupes(cmd);
		return (0);
	}
	fill_dupes(cmd);
	wait_for_exec(cmd, pids, parallel_exec(cmd, pids));
	signal_handler();
	redirect_dupes(cmd);
	if (xclose(&cmd->fdio->stdincpy) == -1)
		perror("minishell (execute_piped_commands) - close (in)");
	if (xclose(&cmd->fdio->stdoutcpy) == -1)
		perror("minishell (execute_piped_commands) - close (out)");
	return (0);
}
