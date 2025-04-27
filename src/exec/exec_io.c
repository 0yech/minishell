/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:17 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/27 06:56:30 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called by the child process.
 * Resets the command given as argument's fds to point to STDOUT and STDIN.
 */
int	close_child(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO)
	{
		dup2(current->fdio->fdin, STDIN_FILENO);
		close(current->fdio->fdin);
	}
	if (current->fdio->fdout != STDOUT_FILENO)
	{
		dup2(current->fdio->fdout, STDOUT_FILENO);
		close(current->fdio->fdout);
	}
	close_all_other_fds(fetch_commands(NULL), current);
	return (0);
}

/**
 * @brief Called by the parent process. Closes the command given as argument's
 * fds, we don't need them as the parent (?).
 */
int	close_parent(t_command *current)
{
	if (current->fdio->fdin > STDERR_FILENO)
	{
		close(current->fdio->fdin);
		current->fdio->fdin = STDIN_FILENO;
	}
	if (current->fdio->fdout > STDERR_FILENO)
	{
		close(current->fdio->fdout);
		current->fdio->fdout = STDOUT_FILENO;
	}
	return (0);
}

static int	set_flags(t_token *arg)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (arg->type == REDIRECT_IN)
		return (flags);
	if (arg->type == REDIRECT_OUT)
		flags |= O_TRUNC;
	else if (arg->type == APPEND)
		flags |= O_APPEND;
	return (flags);
}

/**
 * @brief Setup in and our redirections if applicable by the current
 * arg[i] token.
 */
static void	setup_redirections(t_command *cmd, t_token **arg, int i)
{
	if (arg[i]->type == REDIRECT_IN && arg[i + 1]
		&& arg[i + 1]->type == REDIRECT_FILE)
	{
		if (cmd->fdio->fdin)
			close(cmd->fdio->fdin);
		cmd->fdio->fdin = open(arg[i + 1]->value, O_RDONLY);
		if (cmd->fdio->fdin == -1)
		{
			cmd->isvalid = false;
			perror("minishell (setup_redirections) - open I");
		}
	}
	else if ((arg[i]->type == REDIRECT_OUT || arg[i]->type == APPEND)
		&& arg[i + 1] && arg[i + 1]->type == REDIRECT_FILE)
	{
		if (cmd->fdio->fdout)
			close(cmd->fdio->fdout);
		cmd->fdio->fdout = open(arg[i + 1]->value, set_flags(arg[i]), 0644);
		if (cmd->fdio->fdout == -1)
		{
			cmd->isvalid = false;
			perror("minishell (setup_redirections) - open O");
		}
	}
}

/**
 * @brief Sets up the fds of the command given as argument.
 * Handles heredocs, redirections both in and out of files.
 * @param cmd The command to set up.
 * @param arg The arguments of the command.
 * @return 0 if everything went well, -1 otherwise.
 */
void	setup_io(t_command *cmd, t_token **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i]->type == HEREDOC)
			heredoc_handler(cmd, arg[i + 1]);
		else
			setup_redirections(cmd, arg, i);
		i++;
		if (cmd->isvalid == false)
			close(cmd->fdio->fdout);
	}
}
