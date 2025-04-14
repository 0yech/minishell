/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:19:09 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/14 14:35:42 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param key The key to look for and clear.
 * @return 0 if a key was successfully unset, 1 if the key didn't exist.
 */
int	ft_unset(char *key)
{
	t_env	*node;

	node = env_get_key(key);
	if (!node)
		return (1);
	node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	env_delone(node);
	return (0);
}
