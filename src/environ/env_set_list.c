/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:49:07 by nrey              #+#    #+#             */
/*   Updated: 2025/02/10 18:47:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value_pos(char *str)
{
	while (*str != '=')
		str++;
	return (str);
}

int	env_name_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	fill_env_node(char *envp, t_env *node)
{
	int		namesize;
	int		valuesize;

	namesize = env_name_size(envp);
	valuesize = ft_strlen(env_value_pos(envp));
	node->name = malloc(namesize + 1);
	node->value = malloc(valuesize + 1);
	if (!node->name || !node->value)
		return (free(node->name), free(node->value), 0);
	ft_strlcpy(node->name, envp, namesize + 1);
	ft_strlcpy(node->value, ft_strchr(envp, '=') + 1, valuesize + 1);
	return (1);
}
