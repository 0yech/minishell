/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/03/06 17:18:20 by nrey             ###   ########.fr       */
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

static int	cd_home(void)
{
	char	*old_cwd;
	char	*new_cwd;

	old_cwd = getcwd(NULL, 0);
	if (chdir(get_key("HOME")->value) == 0)
	{
		new_cwd = getcwd(NULL, 0);
		if (cd_update_env(old_cwd, new_cwd) == 0)
			return (0);
		return (free(old_cwd), free(new_cwd), 1);
	}
	return (free(old_cwd), 1);
}

static int	cd_swap_old(void)
{
	char	*pwd;
	char	*old_pwd;

	if (!get_key("OLDPWD"))
		return (printf("[!] - No OLDPWD\n"), 1);
	old_pwd = ft_strdup(get_key("OLDPWD")->value);
	if (get_key("OLDPWD") && chdir(get_key("OLDPWD")->value) == 0)
	{
		pwd = ft_strdup(get_key("PWD")->value);
		if (env_set(ft_strdup("OLDPWD"), pwd) == 2)
			return (printf("[!] cd - Failed to change environment!\n"), 1);
		if (env_set(ft_strdup("PWD"), old_pwd) == 2)
			return (printf("[!] cd - Failed to change environment!\n"), 1);
		return (0);
	}
	printf("[!] - Failed to change directory!\n");
	return (1);
}

static int	cd_dir(t_command *cmd)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = ft_strdup(get_key("PWD")->value);
	if (chdir(cmd->argv[1]) == 0)
	{
		pwd = getcwd(NULL, 0);
		if (cd_update_env(old_pwd, pwd) == 0)
			return (0);
		printf("[!] cd - Failed to change environment!\n");
		return (free(old_pwd), free(pwd), 1);
	}
	printf("[!] - Failed to change directory!\n");
	return (free(old_pwd), 1);
}

int	ft_cd(t_command *cmd)
{
	if (cmd->argv[1] == NULL
		|| !ft_strncmp(cmd->argv[1], "~", 2))
		return (cd_home());
	if (!ft_strncmp(cmd->argv[1], "-", 2))
		return (cd_swap_old());
	return (cd_dir(cmd));
}
