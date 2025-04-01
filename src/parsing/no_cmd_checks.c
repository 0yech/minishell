/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by nrey              #+#    #+#             */
/*   Updated: 2025/03/26 10:39:32 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_firstnode(t_token *current) // UNUSED
{
	if (!current->prev)
		return (1);
	return (0);
}

// int	handle_fake_redirection(t_command *cmd)
// {
// 	int	fd;

// 	// if (cmd->fdio->hd_delim) // just check for HEREDOC tokens
// 	// 	process_heredoc(cmd);
// 	if (cmd->fdio->outtype == RED_OUT)
// 		fd = open(cmd->fdio->output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else if (cmd->fdio->outtype == APD)
// 		fd = open(cmd->fdio->output, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (cmd->fdio->input)
// 		fd = open(cmd->fdio->input, O_RDONLY);
// 	return (fd);
// }

t_command *fill_fake_command(t_token *current)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = ft_strdup(current->value);
	cmd->fdio = ft_calloc(1, sizeof(t_io));
	if (!cmd->fdio)
		return (NULL);
	// fill_args_fds(cmd, current);
	// now replaced with new parsing (setup_redirections)
	return (cmd);
}

int no_cmd_checks(t_token *token_list)
{
	// int			fd;
	t_token		*list;
	t_command	*cmd;

	list = token_list;
	if (list->type != REDIRECT_IN && list->type != REDIRECT_OUT
		&& list->type != APPEND && list->type != HEREDOC)
		return (-1);
	cmd = fill_fake_command(list);
	// fd = handle_fake_redirection(cmd);
	// if (fd >= 0)
	// 	close(fd);
	free_command_list(cmd);
	return (0);
}