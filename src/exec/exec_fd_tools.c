/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:07:00 by nrey              #+#    #+#             */
/*   Updated: 2025/04/27 16:53:23 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"

void	close_all_other_fds(t_command *cmd_list, t_command *current_cmd)
{
	t_command	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp != current_cmd)
		{
			if (tmp->fdio->fdin != STDIN_FILENO && tmp->fdio->fdin > 2)
			{
				if (close(tmp->fdio->fdin) == -1)
					perror("minishell (close_all_other_fds) - close (out)");
				tmp->fdio->fdin = STDIN_FILENO;
			}
			if (tmp->fdio->fdout != STDOUT_FILENO && tmp->fdio->fdout > 2)
			{
				if (close(tmp->fdio->fdout) == -1)
					perror("minishell (close_all_other_fds) - close (in)");
				tmp->fdio->fdout = STDOUT_FILENO;
			}
		}
		tmp = tmp->next;
	}
}
