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
 * In case of error with execve, exits with 126.
 */
int	exec_child(t_command *current)
{
	char	**envtab;

	close_child(current);
	if (ft_strncmp(current->command, "<<", 3) != 0)
	{
		envtab = env_to_char(*env_get());
		if (!envtab)
			return (-1);
		execve(find_executable_path(current->command), current->argv, envtab);
		perror("minishell (exec_child) - execve");
		exit(126);
	}
	return (-1);
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
	if (env_set_key("?", str_exit_status) == -1)
		return (free(str_exit_status), -1);
	free(str_exit_status);
	return (0);
}

int	process_command(t_command *current)
{
	pid_t		pid;
	int			exit_status;
	int			*stat_loc;

	if (is_builtin(current))
	{
		exit_status = exec_pipe_builtin(current);
		exec_update_env(exit_status);
		current = current->next;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (perror("minishell (execute_piped_commands) - fork"), -1);
	if (pid > 0)
		close_parent(current);
	else if (pid == 0)
		exec_child(current);
	stat_loc = ft_calloc(1, sizeof(int));
	if (!stat_loc)
		return (perror("minishell (execute_piped_commands) - ft_calloc"), -1);
	wait(stat_loc);
	exec_update_env(WEXITSTATUS(*stat_loc));
	return (free(stat_loc), 0);
}

int	execute_piped_commands(t_command *cmd)
{
	t_command	*current;

	if (!cmd)
		return (-1);
	cmd->fdio->stdincpy = dup(STDIN_FILENO);
	cmd->fdio->stdoutcpy = dup(STDOUT_FILENO);
	if (cmd->fdio->stdincpy == -1 || cmd->fdio->stdoutcpy == -1)
		return (perror("minishell (execute_piped_commands) - dup"), -1);
	current = cmd;
	while (current)
	{
		setup_redirections(current, current->arguments);
		if (current->command && current->command[0]
			&& process_command(current) == -1)
			return (-1);
		current = current->next;
	}
	dup2(cmd->fdio->stdincpy, STDIN_FILENO);
	dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO);
	if (cmd->fdio->stdincpy == -1 || cmd->fdio->stdoutcpy == -1)
		perror("minishell (execute_piped_commands) - dup2");
	return (0);
}
