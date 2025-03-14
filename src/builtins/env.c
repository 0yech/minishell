/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:33:11 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/12 13:47:22 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	t_env	*tmp;

	tmp = *env_get();
	while (tmp)
	{
		if (write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name)) == -1)
			return (perror("minishell (ft_env) - write"), -1);
		if (write(STDOUT_FILENO, "=", 1) == -1)
			return (perror("minishell (ft_env) - write"), -1);
		ft_putendl_fd(tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
