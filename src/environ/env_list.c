/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:27:02 by nrey              #+#    #+#             */
/*   Updated: 2025/04/16 20:10:32 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The last node of the minishell environment.
 */
t_env	*env_last(void)
{
	t_env	*node;

	node = *env_get();
	while (node && node->next)
		node = node->next;
	return (node);
}

/**
 * @brief Creates a new environment node with the specified key, value,
 * and linked nodes.
 *
 * @return A pointer to the newly created environment node,
 * or NULL on allocation failure.
 */
t_env	*env_new(char *key, char *value, t_env *prev, t_env *next)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (perror("minishell (env_new) - malloc"), NULL);
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
