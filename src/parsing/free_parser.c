/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:50:17 by nrey              #+#    #+#             */
/*   Updated: 2025/02/25 21:58:38 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_delone(t_command *node)
{
    int i;

    i = 0;
	if (node)
	{
		if (node->command)
			free(node->command);
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