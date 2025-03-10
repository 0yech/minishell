/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:33:11 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/09 16:30:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	t_env	*tmp;

	tmp = *env_get();
	while (tmp)
	{
		write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name));
		write(STDOUT_FILENO, "=", 1);
		ft_putendl_fd(tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
