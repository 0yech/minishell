/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:56:38 by nrey              #+#    #+#             */
/*   Updated: 2025/04/16 22:28:01 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Takes in a path string and checks if the file is a directory.
 *
 * @details
 * stat takes a struct stat element (sys/stat.h) and fills it with information
 * first arg is the input, the second one is the struct (*buf)
 *
 * @return false if it's NOT a directory, true if it is
*/
bool	is_dir(char *path)
{
	struct stat	cmdstat;

	ft_memset(&cmdstat, 0, sizeof(cmdstat));
	if (stat(path, &cmdstat) == -1)
		return (false);
	return (S_ISDIR(cmdstat.st_mode));
}

// returns an int depending on the error.
// 2 means command does not exist/not found
// 3 means specified command is a directory
// 4 means command is not executable
// should be replaced by macros and strerror()
int	exec_types(t_command *current)
{
	char	*path;

	if (ft_strncmp(current->command, "<<", 3) == 0)
		return (0);
	if (is_dir(current->command))
		return (3);
	path = find_executable_path(current->command);
	if (!path)
		return (2);
	if (access(path, F_OK) != 0)
		return (free(path), 2);
	if (is_dir(current->command))
		return (free(path), 3);
	if (access(path, F_OK | X_OK) != 0)
		return (free(path), 4);
	free(path);
	return (0);
}

void	print_exec_checks(t_command *current, int code)
{
	if (code == 2)
	{
		exec_update_env(127);
		write(STDERR_FILENO, current->command, ft_strlen(current->command));
		write(STDERR_FILENO, ": command not found\n", 21);
	}
	else if (code == 3)
	{
		exec_update_env(126);
		write(STDERR_FILENO, current->command, ft_strlen(current->command));
		write(STDERR_FILENO, ": is a directory\n", 18);
	}
	else if (code == 4)
	{
		exec_update_env(126);
		perror(current->command);
	}
}

int	exec_checks(t_command *cmd)
{
	int			code;
	int			valid;
	t_command	*current;

	current = cmd;
	code = 0;
	valid = 0;
	while (current && current->command)
	{
		if (is_builtin(current) == 0)
		{
			code = exec_types(current);
			if (code != 0)
				valid = -1;
			print_exec_checks(current, code);
		}
		current = current->next;
	}
	return (valid);
}
