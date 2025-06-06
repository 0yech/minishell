/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:47:58 by nrey              #+#    #+#             */
/*   Updated: 2025/04/14 17:37:32 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*hd_var_expand(char *line)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	if (!line)
		return (NULL);
	new_line = ft_calloc(full_token_size(line) + 1, sizeof(char));
	if (!new_line)
		return (perror("minishell (hd_var_expand) - malloc"), free(line), NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$'
			&& ft_isprint(line[i + 1]) && line[i + 1] != ' ')
			handle_var(line, new_line, &i, &j);
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = 0;
	return (free(line), new_line);
}

/**
 * @brief Called in case of a heredoc delimiter in the cmd argument. Sets up a
 * pipe to replace the input of that command with the heredoc, and calls
 * readline to read input from the terminal. Once the delimiter is found as a
 * whole line of readline, the function stops.
 *
 * @param cmd The command with the heredoc.
 */
void	heredoc_handler(t_command *cmd, t_token *hd_delim)
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
		if (!line || ft_strncmp(line, hd_delim->value,
				ft_strlen(hd_delim->value) + 1) == 0)
			break ;
		if (hd_delim->quoted == false)
			line = hd_var_expand(line);
		if (write(pipefd[1], line, ft_strlen(line)) == -1
			|| write(pipefd[1], "\n", 1) == -1)
			perror("minishell (heredoc_handler) - write");
		free(line);
	}
	if (line)
		free(line);
	if (xclose(&pipefd[1]) == -1)
		perror("minishell (heredoc_handler) - close");
	cmd->fdio->fdin = pipefd[0];
}
