/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:07 by nrey              #+#    #+#             */
/*   Updated: 2025/03/20 20:47:58 by estettle         ###   ########.fr       */
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
 * added, -1 if an error occurred.
 */
int	env_set_key(char *key, char *value)
{
	t_env	*node;
	char	*alloc_key;
	char	*alloc_value;

	if (!key || !*key || !value)
		return (-1);
	alloc_key = ft_strdup(key);
	if (!alloc_key)
		return (perror("minishell (env_set_key) - ft_strdup"), -1);
	alloc_value = ft_strdup(value);
	if (!alloc_value)
		return (perror("minishell (env_set_key) - ft_strdup"), -1);
	node = env_get_key(key);
	if (node)
	{
		free(alloc_key);
		if (node->value)
			free(node->value);
		node->value = alloc_value;
		return (0);
	}
	node = env_last();
	node->next = env_new(alloc_key, alloc_value, node, NULL);
	if (!node->next)
		return (free(alloc_key), free(alloc_value), -1);
	return (1);
}
