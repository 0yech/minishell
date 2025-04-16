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
void	close_child(t_command *current)
{
	if (current->fdio->fdout != STDOUT_FILENO)
	{
		if (close(STDOUT_FILENO) == -1)
			perror("minishell (close_child - stdout) - close");
		dup2(current->fdio->fdout, STDOUT_FILENO);
	}
	if (current->fdio->fdin != STDIN_FILENO)
	{
		if (close(STDIN_FILENO) == -1)
			perror("minishell (close_child - stdin) - close stdin");
		dup2(current->fdio->fdin, STDIN_FILENO);
	}
}

/**
 * @brief Called by the parent process. Closes the command given as argument's
 * fds, we don't need them as the parent (?).
 */
void	close_parent(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO
		&& close(current->fdio->fdin) == -1)
		perror("minishell (close_parent - fdin) - close");
	if (current->fdio->fdout != STDOUT_FILENO
		&& close(current->fdio->fdout) == -1)
		perror("minishell (close_parent - fdin) - close");
}

static int	set_flags(t_token *arg)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (arg->type == HEREDOC || arg->type == REDIRECT_IN)
		return (flags);
	else if (arg->type == REDIRECT_OUT)
		flags |= O_TRUNC;
	else if (arg->type == APPEND)
		flags |= O_APPEND;
	return (flags);
}

static void	setup_hd(t_command *cmd, t_token **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i]->type == HEREDOC)
			heredoc_handler(cmd, arg[i + 1]);
		i++;
	}
}

int	setup_redirections(t_command *cmd, t_token **arg)
{
	int	i;

	i = 0;
	setup_hd(cmd, arg);
	while (arg[i])
	{
		if (arg[i]->type == REDIRECT_IN && arg[i + 1]
			&& arg[i + 1]->type == REDIRECT_FILE)
		{
			cmd->fdio->fdin = open(arg[i + 1]->value, O_RDONLY);
			if (cmd->fdio->fdin == -1)
				return (perror("minishell (setup_redirections) - open I"), -1);
			i++;
			continue ;
		}
		if (arg[i + 1] && arg[i + 1]->type == REDIRECT_FILE)
		{
			cmd->fdio->fdout = open(arg[i + 1]->value, set_flags(arg[i]), 0644);
			if (cmd->fdio->fdout == -1)
				return (perror("minishell (setup_redirections) - open O"), -1);
		}
		i++;
	}
	return (0);
}
