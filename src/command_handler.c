/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/17 11:14:27 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list)
{
	t_command	*cmd;

	cmd = parsing_handler(token_list);
	// printf("%s\n", (*token_list)->value);
	//printf("Executable found : %s\n", find_executable_path(cmd->command));
	//printf("Executable found : %s\n", find_executable_path(cmd->next->command));
	//printf("Executable found : %s\n\n", find_executable_path(cmd->next->next->command));
	if (execute_piped_commands(cmd) == -1)
		printf("[!] - Error while executing command!\n");
	free_command_list(cmd);
}
