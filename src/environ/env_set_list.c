/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:07 by nrey              #+#    #+#             */
/*   Updated: 2025/03/12 13:02:22 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return A pointer to the first '=' character in the string.
 */
char	*env_value_pos(char *str)
{
	// This function could just be replaced with strchr right?
	while (*str != '=')
		str++;
	return (str);
}

/**
 * @return The size of the key size in the key=value pair given as str.
 */
int	env_name_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

/**
 * @brief Fills a node with the contents of an envp string.
 *
 * @param envp A string of the environment as passed to the main() function.
 * @param node The current node we want to fill.
 * @return 0 if there was an error, 1 if all went well.
 */
int	env_fill_node(char *envp, t_env *node)
{
	size_t		namesize;
	size_t		valuesize;

	namesize = env_name_size(envp);
	valuesize = ft_strlen(env_value_pos(envp));
	node->name = ft_calloc(1, namesize + 1);
	node->value = ft_calloc(1, valuesize + 1);
	if (!node->name || !node->value)
		return (0);
	ft_strlcpy(node->name, envp, namesize + 1);
	ft_strlcpy(node->value, ft_strchr(envp, '=') + 1, valuesize + 1);
	return (1);
}

/**
 * @param key A malloced string that will represent the name of the node.
 * @param value A malloced string that will represent the value of the node.
 * @return 0 if an already existing value was updated, 1 if a new value was
 * added, 2 if an error occurred.
 * TODO : try and find a way to not take malloced strings because this is awful
 * TODO: this probably needs better error return values and especially freeing values
 * when errors occur instead of creating a half baked env node.
 */
int	env_set(char *key, char *value)
{
	t_env	*node;
	char	*alloc_key;
	char	*alloc_value;

	if (!key || !*key)
		return (2);
	alloc_key = ft_strdup(key);
	if (!alloc_key)
		return (perror("minishell (env_set) - ft_strdup"), 2);
	alloc_value = alloc_key;
	if (value)
		alloc_value = ft_strdup(value);
	node = get_key(key);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = alloc_value;
		return (0);
	}
	node = env_last();
	node->next = env_new(alloc_key, alloc_value, node, NULL);
	if (!node->next)
		return (2);
	return (1);
}
