/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:53:14 by nrey              #+#    #+#             */
/*   Updated: 2025/03/26 16:25:06 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns a string starting from `str` pointer until the delimiter,  if it
 * found. Puts a NULL character after the delim.
 * Saves the `str` if present inside the `save` static variable.
 *  * @param str A malloced string.
 */
static char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;

	if (str)
		save = str;
	if (!save || *save == '\0')
		return (NULL);
	token = save;
	while (*save && !ft_strchr(delim, *save))
		save++;
	if (*save)
	{
		*save = '\0';
		save++;
	}
	return (token);
}

/**
 * @brief Joins two strings with a '/' character inbetween.
 *
 * @param path The first string to join.
 * @param command The second string to join.
 * @return The joined string.
 */
static char	*join_path_command(char *path, char *command)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(command) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (perror("minishell (join_path_command) - malloc"), NULL);
	full_path[0] = '\0';
	ft_strlcat(full_path, path, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, command, len);
	return (full_path);
}

/**
 * @brief Finds the full path of the executable in a command string.
 *
 * @note `paths` isn't freed until the end because `ft_strtok` holds a static
 * pointer to it.
 * @param command The command to look up, as a string.
 * @return The full path of the command, ready to be executed.
 */
char	*find_executable_path(char *command)
{
	t_env	*path_node;
	char	*paths;
	char	*full_path;
	char	*token;

	path_node = env_get_key("PATH");
	if (!path_node || !path_node->value || ft_strchr(command, '/'))
		return (ft_strdup(command));
	paths = ft_strdup(path_node->value);
	if (!paths)
		return (perror("minishell (find_executable_path) - ft_strdup"), NULL);
	token = ft_strtok(paths, ":");
	while (token)
	{
		full_path = join_path_command(token, command);
		if (!full_path)
			return (free(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (free(paths), full_path);
		free(full_path);
		token = ft_strtok(NULL, ":");
	}
	return (free(paths), NULL);
}
