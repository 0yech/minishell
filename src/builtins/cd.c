/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/02/17 00:57:57 by nrey             ###   ########.fr       */
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
	env_set(str_oldpwd, old_cwd);
	env_set(str_pwd, new_cwd);
	return (0);
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
			printf("made it here and updated env");
			if (cd_update_env(old_cwd, new_cwd) == 0)
				return (0);
			return (free(old_cwd), free(new_cwd), 1);
		}
		return (1);
	}
	if (chdir((*token_list)->next->value) == 0)
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
