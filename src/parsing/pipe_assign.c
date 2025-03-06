/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:16:23 by nrey              #+#    #+#             */
/*   Updated: 2025/03/06 14:06:30 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void assign_pipes(t_command *cmd)
{
    int pipefd[2];
    t_command *current = cmd;

    while (current && current->next)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(123);
        }
        current->fdio->fdout = pipefd[1];    
        current->next->fdio->fdin = pipefd[0];
        current = current->next;
    }
}
