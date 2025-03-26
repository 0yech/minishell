/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:47:58 by nrey              #+#    #+#             */
/*   Updated: 2025/03/26 14:18:26 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called in case of a heredoc delimiter in the cmd argument. Sets up a
 * pipe to replace the input of that command with the heredoc, and calls
 * readline to read input from the terminal. Once the delimiter is found as a
 * whole line of readline, the function stops.
 *
 * @param cmd The command with the heredoc.
 */
void	heredoc_handler(t_command *cmd)
{
	int		pipefd[2];
	char	*line;

	if (!cmd->fdio->hd_delim)
		return ;
	if (pipe(pipefd) == -1)
		return (perror("minishell (heredoc_handler) - pipe"));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(
				line, cmd->fdio->hd_delim, ft_strlen(cmd->fdio->hd_delim)
			) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(pipefd[1]);
	cmd->fdio->fdin = pipefd[0];
}

void	process_heredoc(t_command *cmd)
{
	// Basically unused at this point
	while (cmd)
	{
		if (cmd->fdio->hd_delim)
			heredoc_handler(cmd);
		cmd = cmd->next;
	}
}
