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
		return (perror("minishell (execute_piped_commands) - fork"), -1);
	if (pid == 0)
	{
		if (is_builtin(current))
		{
			close_child(current);
			status = exec_builtin(current);
			env_clear(env_get());
			begone_child();
			exit(status);
		}
		else
			exec_child(current);
	}
	else if (pid > 0)
		close_parent(current);
	signal_handler();
	return (pid);
}

void	wait_for_exec(t_command *cmd, pid_t pids[1024], int *status, int index)
{
	int			j;
	t_command	*tmp;

	j = 0;
	tmp = cmd;
	while (tmp)
	{
		close_parent(tmp);
		tmp = tmp->next;
	}
	while (j < index)
	{
		if (waitpid(pids[j], status, 0) == -1 && errno != EINTR)
			perror("waitpiderror");
		exec_update_env(WEXITSTATUS(*status));
		j++;
	}
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
	t_command	*current;
	pid_t		pids[1024];
	int			i;
	int			status;

	i = 0;
	status = 0;
	if (!cmd)
		return (-1);
	fill_dupes(cmd);
	if (cmd && !cmd->next && is_builtin(cmd))
	{
		setup_io(cmd, cmd->arguments);
		int status = exec_builtin(cmd);
		exec_update_env(status);
		redirect_dupes(cmd);
		return (close(cmd->fdio->stdincpy), close(cmd->fdio->stdoutcpy), 0);
	}
	current = cmd;
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
	wait_for_exec(current, pids, &status, i);
	redirect_dupes(cmd);
	return (close(cmd->fdio->stdincpy), close(cmd->fdio->stdoutcpy), 0);
}
