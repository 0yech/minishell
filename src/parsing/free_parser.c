/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@protonmail    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:26:22 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/03 17:30:34 by fireinside       ###   ########.fr       */
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
		// printf("[!] - Gonna close fd N%d\n", node->fdio->fdout);
		// if (node->fdio->fdout > 2 && close(node->fdio->fdout) == -1)
		// 	perror("minishell (command_delone) - close");
		// printf("[!] - Gonna close fd N%d\n", node->fdio->fdin);
		// if (node->fdio->fdin > 2 && close(node->fdio->fdin) == -1)
		// 	perror("minishell (command_delone) - close");
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
