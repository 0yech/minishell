/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:27:02 by nrey              #+#    #+#             */
/*   Updated: 2025/02/10 18:45:58 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envdelone(t_env *node)
{
	if (node)
	{
		free(node->name);
		free(node->value);
		free(node);
	}
}

void	envclear(t_env **list)
{
	t_env	*tmp;

	while (list && *list)
	{
		tmp = (*list)->next;
		envdelone(*list);
		*list = tmp;
	}
}
