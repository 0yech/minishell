/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/03/14 09:24:38 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: add comments to functions

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
	char	*tmp;

	if (!get_key("OLDPWD"))
		return (printf("minishell (cd_swap_old): OLDPWD is not set!\n"), 1);
	if (!get_key("PWD"))
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
			return (perror("minishell (cd_swap_old) - getcwd"), 1);
		env_set("PWD", tmp);
		free(tmp);
	}
	tmp = ft_strdup(get_key("OLDPWD")->value);
	if (!tmp)
		return (perror("minishell (cd_swap_old) - ft_strdup"), 1);
	if (chdir(tmp) == 0)
	{
		if (env_set("OLDPWD", get_key("PWD")->value) == 2)
			return (free(tmp), printf("minishell: Failed to set OLDPWD!\n"), 1);
		if (env_set("PWD", tmp) == 2)
			return (free(tmp), printf("minishell: Failed to set PWD!\n"), 1);
		return (free(tmp), 0);
	}
	return (perror("minishell (cd_swap_old) - chdir"), free(tmp), 1);
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
