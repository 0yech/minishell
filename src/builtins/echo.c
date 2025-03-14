/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:49:19 by estettle          #+#    #+#             */
/*   Updated: 2025/03/14 15:31:24 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	char	**tmp;

	tmp = cmd->argv + 1;
	while (*tmp)
	{
		if (write(STDOUT_FILENO, *tmp, ft_strlen(*tmp)) == -1)
			return (perror("minishell (ft_echo) - write"), -1);
		if (*(tmp + 1))
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (perror("minishell (ft_echo) - write"), -1);
		tmp++;
	}
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return (perror("minishell (ft_echo) - write"), -1);
	return (0);
}