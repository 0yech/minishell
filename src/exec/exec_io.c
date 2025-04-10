/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:17 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/10 14:41:33 by fireinside       ###   ########.fr       */
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
 * @brief Called by the parent process. Closes the command given as argument's
 * fds, we don't need them as the parent (?).
 */
void	close_parent(t_command *current)
{
	if (current->fdio->fdin != STDIN_FILENO)
		close(current->fdio->fdin);
	if (current->fdio->fdout != STDOUT_FILENO)
		close(current->fdio->fdout);
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
