/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:26:22 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/27 06:47:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the argument of the given command.
 */
void	destroy_arguments(t_token **arguments)
{
	int	i;

	i = 0;
	if (!arguments)
		return ;
	while (arguments[i])
	{
		if (arguments[i]->value)
			free(arguments[i]->value);
		free(arguments[i]);
		i++;
	}
	free(arguments);
}

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
			destroy_arguments(node->arguments);
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
