/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:27:02 by nrey              #+#    #+#             */
/*   Updated: 2025/02/11 13:51:29 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value, t_env *prev, t_env *next)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = key;
	new->value = value;
	new->prev = prev;
	new->next = next;
	return (new);
}

/**
 * @brief Removes the given node and frees its memory.
 *
 * @param node The node to delete.
 */
void	env_delone(t_env *node)
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
void	env_clear(t_env **list)
{
	t_env	*tmp;

	while (list && *list)
	{
		tmp = (*list)->next;
		env_delone(*list);
		*list = tmp;
	}
}
