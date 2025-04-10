/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:07 by nrey              #+#    #+#             */
/*   Updated: 2025/04/10 14:09:01 by fireinside       ###   ########.fr       */
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
 * @return 0 if there was an error, 1 if all went well.
 */
int	env_fill_node(char *envp, t_env *node)
{
	size_t		namesize;
	size_t		valuesize;

	namesize = env_name_size(envp);
	valuesize = ft_strlen(ft_strchr(envp, '='));
	node->name = ft_calloc(1, namesize + 1);
	node->value = ft_calloc(1, valuesize + 1);
	if (!node->name || !node->value)
		return (0);
	ft_strlcpy(node->name, envp, namesize + 1);
	ft_strlcpy(node->value, ft_strchr(envp, '=') + 1, valuesize + 1);
	return (1);
}

int	env_update_var(char	*key, char *alloc_key, char *alloc_value)
{
	t_env	*node;

	node = env_get_key(key);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = alloc_value;
		return (free(alloc_key), 0);
	}
	node = env_last();
	node->next = env_new(alloc_key, alloc_value, node, NULL);
	if (!node->next)
		return (free(alloc_key), free(alloc_value), -1);
	return (1);
}

/**
 * @brief Sets a variable in the minishell environment.
 * 
 * @param key A malloced string that will represent the name of the node.
 * @param value A malloced string that will represent the value of the node.
 * If pointer is NULL, set value of new env node to NULL.
 * @return 0 if an already existing value was updated, 1 if a new value was
 * added, -1 if an error occurred.
 */
// TODO : need "export: `=value`: not a valid identifier" error message
int	env_set_key(char *key, char *value)
{
	char	*alloc_value;
	char	*alloc_key;

	if (!key || !*key)
		return (-1);
	alloc_value = NULL;
	if (value)
	{
		alloc_value = ft_strdup(value);
		if (!alloc_value)
			return (perror("minishell (env_set_key) - malloc"), -1);
	}
	alloc_key = ft_strdup(key);
	if (!alloc_key)
		return (perror("minishell (env_set_key) - malloc"), -1);
	return (env_update_var(key, alloc_key, alloc_value));
}
