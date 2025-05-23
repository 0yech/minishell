/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:07 by nrey              #+#    #+#             */
/*   Updated: 2025/04/16 20:16:30 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The size of the key size in the key=value pair given as str.
 */
static int	env_name_size(char *str)
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
 * @return 0 if all went well, -1 otherwise.
 */
int	env_fill_node(char *envp, t_env *node)
{
	size_t		namesize;
	size_t		valuesize;

	namesize = env_name_size(envp);
	valuesize = ft_strlen(ft_strchr(envp, '='));
	node->name = ft_calloc(1, namesize + 1);
	if (!node->name)
		return (perror("minishell (env_fill_node) - malloc"), -1);
	node->value = ft_calloc(1, valuesize + 1);
	if (!node->value)
		return (perror("minishell (env_fill_node) - malloc"), -1);
	ft_strlcpy(node->name, envp, namesize + 1);
	ft_strlcpy(node->value, ft_strchr(envp, '=') + 1, valuesize + 1);
	return (0);
}

/**
 * @brief Checks if a variable with the given key already exists, then either
 * updates the existing variable or creates a new one at the end of the env
 * list. Sets the value to alloc_value.
 *
 * @return 0 if everything went fine, 1 if an error occurred.
 */
static int	env_update_var(char *alloc_key, char *alloc_value)
{
	t_env	*node;

	node = env_get_key(alloc_key);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = alloc_value;
		return (free(alloc_key), 0);
	}
	node = env_last();
	if (node)
	{
		node->next = env_new(alloc_key, alloc_value, node, NULL);
		if (!node->next)
			return (free(alloc_key), free(alloc_value), 1);
	}
	else
	{
		*(env_get()) = env_new(alloc_key, alloc_value, NULL, NULL);
		if (!*env_get())
			return (free(alloc_key), free(alloc_value), 1);
	}
	return (0);
}

/**
 * @brief Sets a variable in the minishell environment.
 * 
 * @param key A malloced string that will represent the name of the node.
 * @param value A malloced string that will represent the value of the node.
 * If the value pointer is NULL, sets the value of the new env node to NULL.
 * @return 0 if everything went well, 1 if an error occurred.
 */
int	env_set_key(char *key, char *value)
{
	char	*alloc_value;
	char	*alloc_key;

	if (!key || !*key)
		return (1);
	alloc_value = NULL;
	if (value)
	{
		alloc_value = ft_strdup(value);
		if (!alloc_value)
			return (perror("minishell (env_set_key) - malloc"), 1);
	}
	alloc_key = ft_strdup(key);
	if (!alloc_key)
		return (perror("minishell (env_set_key) - malloc"), 1);
	return (env_update_var(alloc_key, alloc_value));
}
