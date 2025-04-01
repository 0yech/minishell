/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:50:17 by nrey              #+#    #+#             */
/*   Updated: 2025/03/24 23:59:41 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_delone(t_command *node)
{
	int	i;

	if (node)
	{
		if (node->command)
			free(node->command);
		free(node->fdio);
		if (node->argv)
		{
			i = 0;
			while (node->argv[i])
				free(node->argv[i++]);
			free(node->argv);
		}
		if (node->arguments)
			free(node->arguments);
		free(node);
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		command_delone(cmd);
		cmd = tmp;
	}
}
