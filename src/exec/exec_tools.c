/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:53:14 by nrey              #+#    #+#             */
/*   Updated: 2025/03/10 09:13:29 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *delim)
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

char	*join_path_command(char *path, char *command)
{
	char	*full_path;
	int		len;

	len = ft_strlen(path) + ft_strlen(command) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	ft_strlcat(full_path, path, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, command, len);
	return (full_path);
}

char	*find_executable_path(char *command)
{
	t_env	*path_node;
	char	*paths;
	char	*full_path;
	char	*token;

	path_node = get_key("PATH");
	if (!path_node || !path_node->value || ft_strchr(command, '/'))
		return (ft_strdup(command));
	paths = ft_strdup(path_node->value);
	if (!paths)
		return (NULL);
	token = ft_strtok(paths, ":");
	while (token)
	{
		//printf("PATH folder test : %s\n", token);
		full_path = join_path_command(token, command);
		//printf("Executable test : %s\n", full_path);
		if (!full_path)
			return (free(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (free(paths), full_path);
		free(full_path);
		token = ft_strtok(NULL, ":");
	}
	return (free(paths), NULL);
}
