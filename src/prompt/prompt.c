/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:02 by nrey              #+#    #+#             */
/*   Updated: 2025/04/07 17:59:39 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Displays the minishell prompt along with git branch information if
 * the current directory is part of a git repo.
 */
void	display_prompt(void)
{
	t_env	*cwd;
	char	*branch;

	cwd = env_get_key("PWD");
	if (cwd == NULL)
	{
		write(2, "minishell (display_prompt) - get_key: $PWD not set", 50);
		return ;
	}
	branch = get_git_branch();
	if (branch)
	{
		printf("\033[1m\033[38;2;255;190;100m(git: %s)"
			"\033[38;2;160;240;130m%s"
			"\033[0m ", branch, cwd->value);
		free(branch);
	}
	else
		printf("\033[1m\033[38;2;160;240;130m%s\033[0m ", cwd->value);
}
