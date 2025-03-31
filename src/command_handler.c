/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/27 14:56:28 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list)
{
	t_command	*cmd;

	cmd = parsing_handler(token_list);
	if (!cmd)
	{
		// Used for valid redirections without commands, currently is being called
		// even when a command node was printed, cause parser returned NULL node,
		// but is checked on start. WARNING - multiple invalid commands will enter this,
		// must yet be taken care of.
		// no_cmd_checks(*token_list);
	}
	// TODO : Single invalid Heredoc should still create an fd when there's one. Only Check it when no command exists, pipe stuff should work fine already.
	// TODO : Empty command list but not empty tokens. Should create fds when needed.
	// TODO : Nvm, pipe multiple heredocs are not fine, they do not create a second command node.

	// TODO : Additional error checks and "parser" for invalid redirections that still need fds

	// TODO TEST : ls | << EOF > out.txt | cat << EOF > out.txt <- This test fails and minishell needs 2 CTRL+D signals to close.
	// TODO, BIG TODO, Exec is broken Probably linked with the issue above ^
	// Once a "custom" fd is set in a command, it will put it in regardless of
	// the commands order. This probably was the reason fds were closed often before.

	//printf("%s\n", (*token_list)->value);
	//printf("Executable found : %s\n", find_executable_path(cmd->command));
	//printf("Executable found : %s\n", find_executable_path(cmd->next->command));
	//printf("Executable found : %s\n\n", find_executable_path(cmd->next->next->command));
	execute_piped_commands(cmd);
	tokens_clear(token_list);
	free_command_list(cmd);
}
