/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:21:22 by nrey              #+#    #+#             */
/*   Updated: 2025/03/27 10:14:09 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called by the child process.
 * Resets the command given as argument's fds to point to STDOUT and STDIN.
 */
void	close_child(t_command *current)
{
	if (current->fdio->fdout != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		dup2(current->fdio->fdout, STDOUT_FILENO);
	}
	if (current->fdio->fdin != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		dup2(current->fdio->fdin, STDIN_FILENO);
	}
}

/**
 * @brief Called by the parent process. Closes the command given as arguemnt's
 * fds, we don't need them as the parent (?).
 */
void	close_parent(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO)
		close(current->fdio->fdin);
	if (current->fdio->fdout != STDOUT_FILENO)
		close(current->fdio->fdout);
}

/**
 * @brief Calls the appropriate builtin according to the name of the command
 * given as argument, and returns its exit status.
 * If the command isn't a builtin, -1 is returned.
 */
int	exec_builtin(t_command *current)
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
	{
		if (!current->argv[1])
			return (ft_export(NULL));
		return (ft_export(current->argv[1]));
	}
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
 * @brief Executes a command as a child process.
 * In case of error with execve, exits with 126.
 */
int exec_child(t_command *current)
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

int	setup_redirections(t_command *cmd, t_token **arg)
{
	int	flags;
	int	i;

	i = 0;
	while (arg[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (arg[i]->type == HEREDOC)
			heredoc_handler(cmd, arg[i + 1]);
		else if (arg[i]->type == REDIRECT_IN && arg[i + 1]
			&& arg[i + 1]->type == REDIRECT_FILE)
		{ 
			cmd->fdio->fdin = open(arg[i + 1]->value, O_RDONLY);
			if (cmd->fdio->fdin == -1)
				return (perror("minishell (setup_redirections) - open (in)"), -1);
			i++;
			continue ;
		}
		else if (arg[i]->type == REDIRECT_OUT)
			flags |= O_TRUNC; // Truncate, overwrites the file
		else if (arg[i]->type == APPEND)
			flags |= O_APPEND; // Append, adds it at the end
		if (arg[i + 1] && arg[i + 1]->type == REDIRECT_FILE)
		{
			cmd->fdio->fdout = open(arg[i + 1]->value, flags, 0644);
			printf("Opened a file for writing: %s\n", arg[i + 1]->value);
			if (cmd->fdio->fdout == -1)
				return (perror("minishell (setup_redirections) - open (out)"), -1);
		}
		i++;
	}
	return (0);
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
			exec_builtin(current);
			close(current->fdio->fdout);
			exit(0);
		}
		stat_loc = ft_calloc(1, sizeof(int));
		if (!stat_loc)
			return (perror("minishell (exec_pipe_builtin) - ft_calloc"), -1);
		wait(stat_loc);
		exit_status = WEXITSTATUS(*stat_loc);
		return (close(current->fdio->fdout), free(stat_loc), exit_status);
	}
	return (exec_builtin(current));
}

/**
 * @brief Updates the environment after attemtping to execute a command.
 * 
 * @details Updates the _ variable with the last argv of the cmd, and the ?
 * variable with the exit_status.
 * 
 * @param cmd The command that was executed (or was attempted, anyway)
 * @param exit_status The exit status returned by the command.
 * @return 0 if all went well, -1 if an error occured with ft_itoa.
 */
int	exec_update_env(t_command *cmd, int exit_status)
{
	char	**tmp;
	int		i;
	char	*str_exit_status;

	tmp = cmd->argv;
	i = 0;
	while (tmp[i] && tmp[i + 1])
		i++;
	env_set_key("_", tmp[i]);
	str_exit_status = ft_itoa(exit_status);
	if (!str_exit_status)
		return (perror("minishell (exec_update_env) - malloc"), -1);
	env_set_key("?", str_exit_status);
	free(str_exit_status);
	return (0);
}

int process_command(t_command *current)
{
	pid_t		pid;
	int			exit_status;
	int			*stat_loc;

	if (is_builtin(current))
	{
		exit_status = exec_pipe_builtin(current);
		exec_update_env(current, exit_status);
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
	exec_update_env(current, WEXITSTATUS(*stat_loc));
	return (free(stat_loc), 0);
}

int execute_piped_commands(t_command *cmd)
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
		if (current->command && process_command(current) == -1)
			return (-1);
		current = current->next;
	}
	dup2(cmd->fdio->stdincpy, STDIN_FILENO);
	dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO);
	if (cmd->fdio->stdincpy == -1 || cmd->fdio->stdoutcpy == -1)
		perror("minishell (execute_piped_commands) - dup2");
	return (0);
}
