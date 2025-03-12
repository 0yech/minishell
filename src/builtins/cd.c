/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/03/12 20:40:05 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_update_env(char *old_pwd, char *new_pwd)
{
	if (!old_pwd)
	{
		if (env_set("OLDPWD", new_pwd) == 2)
		{
			printf("minishell (cd_update_env) - env_set: "
			 "Failed to change environment!\n");
			return (1);
		}
	}
	else
	{
		if (env_set("OLDPWD", old_pwd) == 2)
		{
			printf("minishell (cd_update_env) - env_set: "
			 "Failed to change environment!\n");
			return (1);
		}
	}
	if (env_set("PWD", new_pwd) == 2)
	{
		printf("minishell (cd_update_env) - env_set: "
		 "Failed to change environment!\n");
		return (1);
	}
	return (0);
}

static int	cd_home(void)
{
	t_env	*home;
	char	*old_cwd;

	home = get_key("HOME");
	if (!home)
		return (printf("minishell (cd_home) - get_key: HOME is not set!\n"), 1);
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (perror("minishell (cd_home) - getcwd"), 1);
	if (chdir(home->value) == 0)
	{
		if (cd_update_env(old_cwd, home->value) == 0)
			return (free(old_cwd), 0);
		return (free(old_cwd), 1);
	}
	return (perror("minishell (cd_home) - chdir"), free(old_cwd), 1);
}

static int	cd_swap_old(void)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = get_key("OLDPWD");
	if (!oldpwd)
		return (printf("minishell (cd_swap_old) - "
				  "get_key: OLDPWD is not set!\n"), 1);
	tmp = ft_strdup(oldpwd->value);
	if (!tmp)
		return (perror("minishell (cd_swap_old) - ft_strdup"), 1);
	if (chdir(oldpwd->value) == 0)
	{
		pwd = get_key("PWD");
		if (env_set("OLDPWD", pwd->value) == 2)
			return (printf("minishell (cd_swap_old) - "
				  "envset: Failed to set OLDPWD!\n"), 1);
		if (env_set("PWD", tmp) == 2)
			return (printf("minishell (cd_swap_old) - "
				  "envset: Failed to set PWD!\n"), 1);
		return (0);
	}
	perror("minishell (cd_swap_old) - chdir");
	return (1);
}

static int	cd_dir(t_command *cmd)
{
	t_env	*pwd;
	char	*str_pwd;
	char	*old_pwd;

	pwd = get_key("PWD");
	old_pwd = NULL;
	if (pwd)
		old_pwd = ft_strdup(pwd->value);
	if (chdir(cmd->argv[1]) == 0)
	{
		str_pwd = getcwd(NULL, 0);
		if (!str_pwd)
			return (perror("minishell (cd_dir) - getcwd"), 1);
		if (cd_update_env(old_pwd, str_pwd) == 0)
			return (free(old_pwd), free(str_pwd), 0);
		return (free(old_pwd), free(str_pwd), 1);
	}
	perror("minishell (cd_swap_old) - chdir");
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
