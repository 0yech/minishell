/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/02/13 20:06:22 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_update_env(char *old_cwd, char *new_cwd)
{
	char	*str_oldpwd;
	char	*str_pwd;

	str_oldpwd = ft_strdup("OLDPWD");
	if (!str_oldpwd)
		return (1);
	str_pwd = ft_strdup("PWD");
	if (!str_pwd)
		return (free(str_oldpwd), 1);
	if (env_set(str_oldpwd, old_cwd) == 2)
		return (free(str_pwd), 2);
	if (env_set(str_pwd, new_cwd) == 2)
		return (3);
	return (0);
}

int	ft_cd(t_token **token_list)
{
	char	*old_cwd;
	char	*new_cwd;

	if ((*token_list)->next == NULL)
	{
		old_cwd = getcwd(NULL, 0);
		if (chdir(get_key("HOME")->value) == 0)
			return (0);
		new_cwd = getcwd(NULL, 0);
		if (cd_update_env(old_cwd, new_cwd) == 0)
			return (0);
		free(old_cwd);
		free(new_cwd);
		return (1);
	}
	if (chdir((*token_list)->next->value) == 0)
	{
		old_cwd = getcwd(NULL, 0);
		printf("[!] - Switched working directory to %s\n",
			(*token_list)->next->value);
		cd_update_env(old_cwd, getcwd(NULL, 0));
		return (0);
	}
	printf("[!] - Failed to change working directory!\n");
	return (1);
}
