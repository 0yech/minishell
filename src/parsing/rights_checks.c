/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:56:38 by nrey              #+#    #+#             */
/*   Updated: 2025/04/17 18:52:05 by nrey             ###   ########.fr       */
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

/**
 * @brief Determines the type of a given command and returns
 * an appropriate code.
 *
 * @return An integer that corresponds to the result of the checks:
 * - 0: Command is valid and executable.
 * - 2: Command not found or inaccessible.
 * - 3: Command is a directory.
 * - 4: Command exists but is not executable.
 */
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
	if (access(path, F_OK) == -1)
		return (free(path), 2);
	if (is_dir(current->command) == true)
		return (free(path), 3);
	if (access(path, F_OK | X_OK) == -1)
		return (free(path), 4);
	free(path);
	return (0);
}

/**
 * @brief Prints an appropriate error message depending on the code.
 *
 * @param current The command related to the error code.
 * @param code 2: Command not found or inaccessible. 3: Command is a directory.
 * 4: Command exists but is not executable.
 */
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

/**
 * @brief Executes validation checks on a list of commands
 * and sets their validity.
 *
 * @param cmd A pointer to the head of the t_command list.
 */
void	exec_checks(t_command *cmd)
{
	int			code;
	t_command	*current;

	current = cmd;
	code = 0;
	while (current && current->command)
	{
		if (is_builtin(current) == 0)
		{
			code = exec_types(current);
			if (code != 0)
				current->isvalid = false;
			else
				current->isvalid = true;
			print_exec_checks(current, code);
		}
		current = current->next;
	}
}
