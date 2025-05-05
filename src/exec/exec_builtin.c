/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:39:04 by fireinside        #+#    #+#             */
/*   Updated: 2025/05/05 20:09:19 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees tokens and commands in the current process.
 *
 * @details Calls the fetch_tokens and fetch_commands static getters
 * to get the current process' lexer tokens and commands.
 */
void	clear_data(void)
{
	t_token		**tokenlist;
	t_command	*cmdlist;

	tokenlist = fetch_tokens(NULL);
	cmdlist = fetch_commands(NULL);
	if (tokenlist)
	{
		tokens_clear(tokenlist);
		free(tokenlist);
	}
	if (cmdlist)
	{
		close_all_fds(cmdlist);
		free_command_list(cmdlist);
	}
}

/**
 * @brief Checks if the current command is a minishell builtin.
 *
 * @return 1 if the command is a builtin, 0 otherwise.
 */
int	is_builtin(t_command *current)
{
	if (!current || !current->command)
		return (0);
	if (ft_strncmp(current->command, "cd", 3) == 0
		|| ft_strncmp(current->command, "env", 4) == 0
		|| ft_strncmp(current->command, "export", 7) == 0
		|| ft_strncmp(current->command, "unset", 6) == 0
		|| ft_strncmp(current->command, "pwd", 4) == 0
		|| ft_strncmp(current->command, "echo", 5) == 0
		|| ft_strncmp(current->command, "exit", 5) == 0)
	{
		current->isvalid = true;
		return (1);
	}
	return (0);
}

/**
 * @brief Calls the appropriate builtin according to the name of the command
 * given as an argument and returns its exit status.
 * If the command isn't a builtin, -1 is returned.
 */
int	exec_builtin(t_command *current)
{
	if (!current->next)
		close_child(current);
	if (current->isvalid == false)
		return (1);
	if (ft_strncmp(current->command, "cd", 3) == 0)
		return (ft_cd(current));
	if (ft_strncmp(current->command, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(current->command, "env", 4) == 0)
		return (ft_env());
	if (ft_strncmp(current->command, "export", 7) == 0)
		return (ft_export(current));
	if (ft_strncmp(current->command, "unset", 6) == 0)
	{
		if (!current->argv[1])
			return (printf("unset : not enough arguments\n"), -1);
		return (ft_unset(current->argv[1]));
	}
	if (ft_strncmp(current->command, "echo", 5) == 0)
		return (ft_echo(current));
	if (ft_strncmp(current->command, "exit", 5) == 0)
		return (ft_exit(current, 0));
	return (-1);
}
