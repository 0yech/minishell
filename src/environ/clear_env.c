/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:27:02 by nrey              #+#    #+#             */
/*   Updated: 2025/02/11 10:25:53 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes the given node and frees its memory.
 *
 * @param node The node to delete.
 */
void	envdelone(t_env *node)
{
	if (node)
	{
		if (node->name)
			free(node->name);
		if (node->value)
			free(node->value);
		free(node);
	}
}

/**
 * @brief Clears the entire environment list given as parameter.
 *
 * @param list The env list to clear.
 */
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
