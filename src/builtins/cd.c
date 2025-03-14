/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/03/14 10:25:39 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates the environment variables PWD and OLDPWD with the values
 * contained withing new_pwd and old_pwd respectively. Called by the cd builtin.
 *
 * @param old_pwd A string to replace OLDPWD with.
 * @param new_pwd A string to replace PWD with.
 * @return 0 if everything went well, 1 if an error occurred.
 */
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

/**
 * @brief Changes the current working directory according to the given path.
 *
 * @return 0 if everything went well, -1 if an error occurred.
 */
static int	cd_dir(char *path)
{
	t_env	*pwd;
	char	*str_pwd;
	char	*old_pwd;

	if (!get_key("PWD"))
	{
		str_pwd = getcwd(NULL, 0);
		if (!str_pwd)
			return (perror("minishell (cd_dir) - getcwd"), 1);
		env_set("PWD", str_pwd);
		free(str_pwd);
	}
	pwd = get_key("PWD");
	old_pwd = ft_strdup(pwd->value);
	if (chdir(path) == 0)
	{
		str_pwd = getcwd(NULL, 0);
		if (!str_pwd)
			return (perror("minishell (cd_dir) - getcwd"), -1);
		if (cd_update_env(old_pwd, str_pwd) == 0)
			return (free(old_pwd), free(str_pwd), 0);
		return (free(old_pwd), free(str_pwd), -1);
	}
	perror("minishell (cd_swap_old) - chdir");
	return (free(old_pwd), -1);
}

/**
 * @brief "cd" minishell builtin. Handles "cd <dir>", as well as "cd -"
 * and "cd".
 *
 * @param cmd The cd command token.
 * @return 0 if all went well, -1 if an error occurred.
 */
int	ft_cd(t_command *cmd)
{
	t_env	*var;

	if (cmd->argv[1] == NULL
		|| !ft_strncmp(cmd->argv[1], "~", 2))
	{
		var = get_key("HOME");
		if (!var || !var->value)
			return (printf("minishell (ft_cd): $HOME is not set!\n"), -1);
		return (cd_dir(var->value));
	}
	if (!ft_strncmp(cmd->argv[1], "-", 2))
	{
		var = get_key("OLDPWD");
		if (!var || !var->value)
			return (printf("minishell (ft_cd): $OLDPWD is not set!\n"), -1);
		return (cd_dir(var->value));
	}
	return (cd_dir(cmd->argv[1]));
}
