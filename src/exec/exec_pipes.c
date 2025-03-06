/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:21:22 by nrey              #+#    #+#             */
/*   Updated: 2025/03/06 17:58:13 by nrey             ###   ########.fr       */
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

int		exec_builtin(t_command *current)
{
	if (ft_strncmp(current->command, "cd", 3) == 0)
		return (ft_cd(current));
	if (ft_strncmp(current->command, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(current->command, "env", 4) == 0)
		return (ft_env());
	if (ft_strncmp(current->command, "export", 7) == 0)
	{
		if (current->argv[1])
			ft_export(current->argv[1]);
		else
			ft_export(NULL);
	}
	if (ft_strncmp(current->command, "unset", 6) == 0)
	{
		if (current->argv[1])
			ft_unset(current->argv[1]);
		else
			printf("unset : not enough arguments\n");
	}	
	return (127);
}

int		is_builtin(t_command *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current->command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(current->command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(current->command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(current->command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(current->command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(current->command, "pwd", 4) == 0)
		return (1);
	return (0);
}

void	exec_child(t_command *current)
{
	close_child(current);
	execve(find_executable_path(current->command), current->argv, NULL);
	perror("execve");
	exit(124);
}

void	execute_piped_commands(t_command *cmd)
{
	pid_t   pid;
	t_command *current;

	if (!cmd)
		return ;
	current = cmd;
	cmd->fdio->stdincpy = dup(STDIN_FILENO);
	cmd->fdio->stdoutcpy = dup(STDOUT_FILENO);
	while (current)
	{
		if (is_builtin(current))
		{
			exec_builtin(current);
			current = current->next;
			continue ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(124);
		}
		if (pid > 0)
			close_parent(current);
		if (pid == 0)
			exec_child(current);
		current = current->next;
	}
	while (wait(NULL) > 0);
	dup2(cmd->fdio->stdincpy, STDIN_FILENO);
	dup2(cmd->fdio->stdoutcpy, STDOUT_FILENO);
}