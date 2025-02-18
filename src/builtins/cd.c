/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/02/18 14:12:12 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_update_env(char *old_cwd, char *new_cwd)
{
	char	*str_oldpwd;
	char	*str_pwd;

	str_oldpwd = ft_strdup("OLDPWD");
	if (!str_oldpwd)
		return (free(str_oldpwd), 1);
	str_pwd = ft_strdup("PWD");
	if (!str_pwd)
		return (free(str_pwd), 1);
	if (env_set(str_oldpwd, old_cwd) == 2)
		return (free(str_oldpwd), free(str_pwd), 1);
	if (env_set(str_pwd, new_cwd) == 2)
		return (free(str_pwd), 1);
	return (0);
}

static int	cd_swap_old(void)
{
	char	*pwd;
	char	*old_pwd;

	if (get_key("OLDPWD") && chdir(get_key("OLDPWD")->value) == 0)
	{
		old_pwd = ft_strdup(get_key("OLDPWD")->value);
		pwd = ft_strdup(get_key("PWD")->value);
		if (env_set(ft_strdup("OLDPWD"), pwd) == 2)
			return (1);
		if (env_set(ft_strdup("PWD"), old_pwd) == 2)
			return (1);
		return (0);
	}
	return (1);
}

int	ft_cd(t_token **token_list)
{
	char	*old_cwd;
	char	*new_cwd;

	old_cwd = getcwd(NULL, 0);
	if ((*token_list)->next == NULL || !ft_strncmp((*token_list)->next->value, "~", 1))
	{
		if (chdir(get_key("HOME")->value) == 0)
		{
			new_cwd = getcwd(NULL, 0);
			if (cd_update_env(old_cwd, new_cwd) == 0)
				return (0);
			return (free(old_cwd), free(new_cwd), 1);
		}
	}
	else if (!ft_strncmp((*token_list)->next->value, "-", 1))
		return (free(old_cwd), cd_swap_old(), 0);
	else if (chdir((*token_list)->next->value) == 0)
	{
		printf("[!] - Switched working directory to %s\n",
			(*token_list)->next->value);
		new_cwd = getcwd(NULL, 0);
		if (cd_update_env(old_cwd, new_cwd) == 0)
			return (0);
		return (free(old_cwd), free(new_cwd), 1);
	}
	free(old_cwd);
	printf("[!] - Failed to change working directory!\n");
	return (1);
}
