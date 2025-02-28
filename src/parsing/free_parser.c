/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:50:17 by nrey              #+#    #+#             */
/*   Updated: 2025/02/28 01:03:40 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_fds(t_command *node)
{
    if (node)
    {
        if (node->fdio->input)
            free(node->fdio->input);
        if (node->fdio->output)
            free(node->fdio->output);
        if (node->fdio->hd_delim)
            free(node->fdio->hd_delim);
        free(node->fdio);
    }
}

void	parser_delone(t_command *node)
{
    int i;

    i = 0;
	if (node)
	{
		if (node->command)
			free(node->command);
        free_fds(node);
		if (node->argv)
        {
			while (node->argv[i])
            {
                free(node->argv[i]);
                i++;
            }
            free(node->argv);
        }
		free(node);
	}
}

void    free_command_list(t_command *cmd)
{
    t_command   *tmp;
    
    while (cmd)
    {
        tmp = cmd->next;
        parser_delone(cmd);
        cmd = tmp;
    }
}