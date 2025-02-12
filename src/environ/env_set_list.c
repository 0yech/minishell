/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:07 by nrey              #+#    #+#             */
/*   Updated: 2025/02/12 15:04:31 by estettle         ###   ########.fr       */
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
 * @return 0 if an already existing value was updated, 1 if a new value was
 * added, 2 if an error occurred.
 */
int	env_set(char *key, char *value)
{
	// TODO: this probably needs better error return values and especially freeing values
	// when errors occur instead of creating a half baked env node.
	t_env	*node;
	t_env	*new;

	if (!key || !*key)
		return (2);
	if (!value)
		value = key;
	node = get_key(key);
	if (node)
	{
		if (node->value)
			free(node->value);
        node->value = ft_strdup(value);
		if (!node->value)
			return (2);
		return (0);
	}
	node = env_last();
	new = env_new(key, value, node, NULL);
	if (!new)
		return (2);
	node->next = new;
	return (1);
}
