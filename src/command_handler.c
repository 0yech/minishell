/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/24 17:22:06 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list)
{
	t_command	*cmd;

	cmd = parsing_handler(token_list);
	// TODO : Single invalid Heredoc should still create an fd when there's one. Only Check it when no command exists, pipe stuff should work fine already.
	// TODO : Empty command list but not empty tokens. Should create fds when needed.

	// TODO : Additional error checks and "parser" for invalid redirections that still need fds
	// TODO TEST : ls | << EOF > out.txt | cat << EOF > out.txt <- This test fails and minishell needs 2 CTRL+D signals to close.
	//printf("%s\n", (*token_list)->value);
	//printf("Executable found : %s\n", find_executable_path(cmd->command));
	//printf("Executable found : %s\n", find_executable_path(cmd->next->command));
	//printf("Executable found : %s\n\n", find_executable_path(cmd->next->next->command));
	tokens_clear(token_list);
	execute_piped_commands(cmd);
	free_command_list(cmd);
}
