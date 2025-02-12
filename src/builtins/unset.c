/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:19:09 by estettle          #+#    #+#             */
/*   Updated: 2025/02/12 13:32:01 by estettle         ###   ########.fr       */
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

	node = get_key(key);
	if (!node)
		return (1);
	node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	env_delone(node);
	return (0);
}