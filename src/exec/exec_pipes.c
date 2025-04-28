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
	int		exit_code;

	envtab = env_to_char(*env_get());
	if (!envtab)
	{
		begone_child();
		exit(126);
	}
	if (current->fdio)
		child_fdio_redirections(current);
	if (current->exec_code != 0)
	{
		exit_code = get_exitno(current->exec_code);
		print_exec_checks(current, current->exec_code);
		env_clear(env_get());
		free_array(envtab);
		begone_child();
		exit(exit_code);
	}
	close_child(current);
	execve(find_executable_path(current->command), current->argv, envtab);
	perror("minishell (exec_child) - execve");
	begone_child();
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

	pid = fork();
	if (pid == -1)
		return (perror("minishell (execute_piped_commands) - fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (is_builtin(current))
		{
			close_child(current);
			status = exec_builtin(current);
			env_clear(env_get());
			begone_child();
			exit(status);
		}
		exec_child(current);
	}
	else if (pid > 0)
		close_parent(current);
	return (pid);
}

void	wait_for_exec(t_command *cmd, pid_t pids[MAX_PID], int index)
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
	fill_dupes(cmd);
	if (cmd && !cmd->next && is_builtin(cmd))
	{
		setup_io(cmd, cmd->arguments);
		exec_update_env(exec_builtin(cmd));
		redirect_dupes(cmd);
		return (close(cmd->fdio->stdincpy), close(cmd->fdio->stdoutcpy), 0);
	}
	wait_for_exec(cmd, pids, parallel_exec(cmd, pids));
	redirect_dupes(cmd);
	return (close(cmd->fdio->stdincpy), close(cmd->fdio->stdoutcpy), 0);
}
