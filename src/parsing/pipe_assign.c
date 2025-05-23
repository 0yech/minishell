/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:16:23 by nrey              #+#    #+#             */
/*   Updated: 2025/03/10 12:11:39 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Goes through the command list and sets pipe fds for good communication
 * between commands.
 */
void	assign_pipes(t_command *cmd_list)
{
	int			pipefd[2];
	t_command	*current;

	current = cmd_list;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("minishell (assign_pipes) - pipe");
				exit(1);
			}
			current->fdio->fdout = pipefd[1];
			current->next->fdio->fdin = pipefd[0];
		}
		else
			current->fdio->fdout = STDOUT_FILENO;
		current = current->next;
	}
}
