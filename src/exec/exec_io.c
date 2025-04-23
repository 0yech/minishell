/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:17 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/16 20:43:34 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called by the child process.
 * Resets the command given as argument's fds to point to STDOUT and STDIN.
 */
int	close_child(t_command *current)
{
	if (current->fdio->fdout != STDOUT_FILENO)
	{
		if (close(STDOUT_FILENO) == -1)
			return (perror("minishell (close_child - stdout) - close"), -1);
		dup2(current->fdio->fdout, STDOUT_FILENO);
	}
	if (current->fdio->fdin != STDIN_FILENO)
	{
		if (close(STDIN_FILENO) == -1)
			return (perror("minishell (close_child - stdin) - close"), -1);
		dup2(current->fdio->fdin, STDIN_FILENO);
	}
	return (0);
}

/**
 * @brief Called by the parent process. Closes the command given as argument's
 * fds, we don't need them as the parent (?).
 */
int	close_parent(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO
		&& close(current->fdio->fdin) == -1)
		return (perror("minishell (close_parent - fdin) - close"), -1);
	if (current->fdio->fdout != STDOUT_FILENO
		&& close(current->fdio->fdout) == -1)
		return (perror("minishell (close_parent - fdin) - close"), -1);
	return (0);
}

static int	set_flags(t_token *arg)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (arg->type == HEREDOC || arg->type == REDIRECT_IN)
		return (flags);
	if (arg->type == REDIRECT_OUT)
		flags |= O_TRUNC;
	else if (arg->type == APPEND)
		flags |= O_APPEND;
	return (flags);
}

/**
 * @brief Sets up the fds of the command given as argument.
 * @param cmd The command to set up.
 * @param arg The arguments of the command.
 * @return 0 if everything went well, -1 otherwise.
 */
int	setup_redirections(t_command *cmd, t_token **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i]->type == HEREDOC)
			heredoc_handler(cmd, arg[i + 1]);
		else if (arg[i]->type == REDIRECT_IN && arg[i + 1]
			&& arg[i + 1]->type == REDIRECT_FILE)
		{
			cmd->fdio->fdin = open(arg[i + 1]->value, O_RDONLY);
			if (cmd->fdio->fdin == -1)
			{
				cmd->isvalid = false;
				perror("minishell (setup_redirections) - open I");
			}
		}
		else if (arg[i]->type == REDIRECT_OUT
			&& arg[i + 1] && arg[i + 1]->type == REDIRECT_FILE)
		{
			cmd->fdio->fdout = open(arg[i + 1]->value, set_flags(arg[i]), 0644);
			if (cmd->fdio->fdout == -1)
			{
				cmd->isvalid = false;
				perror("minishell (setup_redirections) - open O");
			}
		}
		i++;
	}
	return (0);
}
