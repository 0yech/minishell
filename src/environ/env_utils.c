/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:08:56 by estettle          #+#    #+#             */
/*   Updated: 2025/02/13 16:54:23 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Searches through the environment of the shell for a node matching the
 * provided key.
 *
 * @param key The key string to look up.
 * @return A pointer to the env node containing the key we're searching for. If
 * no node was found containing it, return the last node of the environment.
 */
t_env	*get_key(char *key)
{
	t_env	*tmp;

	if (!key || !*key)
		return (NULL);
	tmp = *env_get();
	while (tmp)
	{
		if (ft_strlen(key) == ft_strlen(tmp->name)
			&& ft_strncmp(key, tmp->name, ft_strlen(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
