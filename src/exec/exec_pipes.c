/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:21:22 by nrey              #+#    #+#             */
/*   Updated: 2025/03/17 11:27:54 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_child(t_command *current)
{
	if (current->fdio->fdout != 1)
	{
		dup2(current->fdio->fdout, STDOUT_FILENO);
		close(current->fdio->fdout);
	}
	if (current->fdio->fdin != 0)
	{
		dup2(current->fdio->fdin, STDIN_FILENO);
		close(current->fdio->fdin);
	}
}

void	close_parent(t_command *current)
{
	if (current->fdio->fdin != 0)
		close(current->fdio->fdin);
	if (current->fdio->fdout != 1)
		close(current->fdio->fdout);
}

// TODO Need to take into account int return values of builtins
int	exec_builtin(t_command *current)
{
	if (ft_strncmp(current->command, "cd", 3) == 0)
		return (ft_cd(current));
	if (ft_strncmp(current->command, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(current->command, "env", 4) == 0)
		return (ft_env());
	if (ft_strncmp(current->command, "export", 7) == 0)
	{
		if (!current->argv[1])
			return(ft_export(NULL));
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

int	is_builtin(t_command *current)
{
	if (!current)
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

int exec_child(t_command* current)
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
	}
	return (-1);
}

void	setup_redirections(t_command *cmd)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->fdio->output) // setup output
	{
		if (cmd->fdio->outtype == RED_OUT)
			flags |= O_TRUNC; // Truncate, overwrites the file
		else if (cmd->fdio->outtype == APD)
			flags |= O_APPEND; // Append, adds it at the end
		cmd->fdio->fdout = open(cmd->fdio->output, flags, 0644);
		if (cmd->fdio->fdout == -1)
		{
			perror("minishell (setup_redirections) - open (output)");
			exit(1);
		}
		if (cmd->next) // Close pipes when an fd redirection is active
    	{
        	close(cmd->next->fdio->fdin);
        	cmd->next->fdio->fdin = open("/dev/null", O_RDONLY);
    	}
	}
	if (cmd->fdio->input) // setup input
	{
		cmd->fdio->fdin = open(cmd->fdio->input, O_RDONLY);
		if (cmd->fdio->fdin == -1)
		{
			perror("minishell (setup_redirections) - open (input)");
			exit(1);
		}
	}
}

int	exec_pipe_builtin(t_command *current)
{
	int pid;

	if (is_builtin(current))
	{
		if (current->next)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("minishell (exec_pipe_builtin) - fork");
				exit(1);
			}
			if (pid == 0)
			{
				close_child(current);
				exec_builtin(current);
				close(current->fdio->fdout);
				exit(0);
			}
			return (close(current->fdio->fdout), 1);
		}
		exec_builtin(current);
		return (1);
	}
	return (0);
}

int execute_piped_commands(t_command* cmd)
{
	pid_t		pid;
	t_command	*current;

	if (!cmd)
		return (-1);
	current = cmd;
	cmd->fdio->stdincpy = dup(STDIN_FILENO);
	cmd->fdio->stdoutcpy = dup(STDOUT_FILENO);
	if (cmd->fdio->stdincpy == -1 || cmd->fdio->stdoutcpy == -1)
		return(perror("minishell (execute_piped_commands) - dup"), -1);
	while (current)
	{
		setup_redirections(current);
		if (exec_pipe_builtin(current))
		{
			current = current->next;
			continue ;
		}
		pid = fork();
		if (pid == -1)
            return(perror("minishell (execute_piped_commands) - fork"), -1);
		if (pid > 0)
			close_parent(current);
		if (pid == 0)
			exec_child(current);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	dup2(cmd->fdio->stdincpy, STDIN_FILENO);
	dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO);
	if (cmd->fdio->stdincpy == -1 || cmd->fdio->stdoutcpy == -1)
		perror("minishell (execute_piped_commands) - dup2");
	return (0);
}
