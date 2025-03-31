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
void	heredoc_handler(t_command *cmd, char *hd_delim)
{
	int		pipefd[2];
	char	*line;

	if (!cmd || !hd_delim)
		return ;
	if (pipe(pipefd) == -1)
		return (perror("minishell (heredoc_handler) - pipe"));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, hd_delim, ft_strlen(line + 1)) == 0)
			break ;
		if (write(pipefd[1], line, ft_strlen(line)) == -1)
			perror("minishell (heredoc_handler) - write");
		if (write(pipefd[1], "\n", 1) == -1)
			perror("minishell (heredoc_handler) - write");
        free(line);
	}
	if (line)
		free(line);
	if (close(pipefd[1]) == -1)
		perror("minishell (heredoc_handler) - close");
	cmd->fdio->fdin = pipefd[0];
}
