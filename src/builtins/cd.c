/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/02/12 15:21:29 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_update_env(char *old_pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (env_set("OLDPWD", old_pwd) == 2)
		return (free(old_pwd), free(cwd), 1);
	if (env_set("PWD", cwd) == 2)
		return (free(cwd), 2);
	return (0);
}

int	ft_cd(t_token **token_list)
{
	char	*cwd;

	if ((*token_list)->next == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (chdir(get_key("HOME")->value) == 0 && cd_update_env(cwd) == 0)
			return (0);
		return (1);
	}
	if (chdir((*token_list)->next->value) == 0)
	{
		cwd = getcwd(NULL, 0);
		printf("[!] - Switched working directory to %s\n",
			(*token_list)->next->value);
		cd_update_env(cwd);
		return (0);
	}
	printf("[!] - Failed to change working directory!\n");
	return (1);
}
