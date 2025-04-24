/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/27 14:56:28 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Static getter for the current token list.
 * @param token_list If the pointer is set, sets the static contained in the
 * function to the pointer provided.
 */
t_token	**fetch_tokens(t_token **token_list)
{
	static t_token	**staticlist;

	if (token_list != NULL)
		staticlist = token_list;
	return (staticlist);
}

/**
 * @brief Static getter for the current command list.
 * @param command_list If the pointer is set, sets the static contained in the
 * function to the pointer provided.
 */
t_command	*fetch_commands(t_command *command_list)
{
	static t_command	*staticlist;

	if (command_list != NULL)
		staticlist = command_list;
	return (staticlist);
}

void	command_handler(t_token **token_list)
{
	t_command	*cmd;

	cmd = parsing_handler(token_list);
	if (!cmd)
		return (tokens_clear(token_list), free(token_list));
	fetch_tokens(token_list);
	fetch_commands(cmd);
	execute_piped_commands(cmd);
	begone_child();
}
