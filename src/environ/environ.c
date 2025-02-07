/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:50:52 by estettle          #+#    #+#             */
/*   Updated: 2025/02/07 16:15:34 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***get_env(void)
{
	static char	**env;

	return &env;
}

void	init_env(char **envp)
{
	int		i;
	char	***env;

	i = 0;
	env = get_env();
	if (*env)
		return ;
	while (envp[i])
	{
		ft_strlcpy((*env)[i], envp[i], ft_strlen(envp[i]));
		i++;
	}
}
