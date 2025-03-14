/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:56:38 by nrey              #+#    #+#             */
/*   Updated: 2025/03/14 11:56:39 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stat takes a struct stat element (sys/stat.h) and fills it with information
// first arg is the input, the second one is the struct (*buf)
// returns false if it's NOT a directory

bool   is_cmd_dir(char *cmd)
{
	struct stat	cmdstat;

	ft_memset(&cmdstat, 0, sizeof(cmdstat));
	stat(cmd, &cmdstat);
	return (S_ISDIR(cmdstat.st_mode));
}

// returns an int depending on the error.
// 2 means command does not exist/not found
// 3 means specified command is a directory
// 4 means command is not executable
// should be replaced by macros and strerror()

int    exec_types(t_command *current)
{
	char *path;

	if (is_cmd_dir(current->command))
		return (3);
	path = find_executable_path(current->command);
	if (!path)
		return (2);
	if (access(path, F_OK) != 0)
		return (free(path), 2);
	else if (is_cmd_dir(current->command))
		return (free(path), 3);
	else if (access(path, F_OK | X_OK) != 0)
		return (free(path), 4);
	free(path);
	return (0);
}

int	exec_checks(t_command *cmd)
{
	int code;
	t_command *current;

	current = cmd;
	while (current)
	{
		code = exec_types(current);
		if (code == 2)
			return (printf("\nCommand not found\n"), 1);
		if (code == 3)
			return (printf("\nIs a directory\n"), 1);
		if (code == 4)
			return (printf("\nCan't execute\n"), 1);
		current = current->next;
	}
	return (0);
}