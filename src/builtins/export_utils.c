/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:35:32 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/12 16:36:56 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compares the env token given in argument with the list of tokens also
 * passed as argument, and returns the next token in alphabetical order,
 * starting from the minimum token.
 * If NULL is passed as the minimum, returns the lowest ranked token.
 */
t_env	*find_lowest_str(t_env *lst, t_env *min)
{
	t_env	*lowest;

	if (min)
		while (ft_strncmp(lst->name, min->name, ft_strlen(lst->name) + 1)
			<= 0)
			lst = lst->next;
	lowest = lst;
	while (lst)
	{
		if (min)
		{
			if (ft_strncmp(lst->name, lowest->name, ft_strlen(lst->name) + 1)
				< 0
				&& ft_strncmp(lst->name, min->name, ft_strlen(lst->name) + 1)
				> 0)
			{
				lowest = lst;
			}
		}
		else if ((ft_strncmp(lst->name, lowest->name, ft_strlen(lst->name) + 1)
				< 0))
			lowest = lst;
		lst = lst->next;
	}
	return (lowest);
}

/**
 * @brief Returns the size of the variable after the new_value is added to it.
 * Just returns the length of new_value if the var doesn't exist yet.
 */
size_t	export_concat_size(t_env *var, char *new_value)
{
	size_t	tot_size;

	tot_size = ft_strlen(new_value);
	if (var && var->value)
		tot_size += ft_strlen(var->value);
	return (tot_size + 1);
}

int	export_value(t_command *cmd, char *tmp, int i)
{
	char	*key;
	char	*value;
	int		return_value;

	key = malloc(tmp - cmd->argv[i] + 1);
	if (!key)
		return (perror("minishell (ft_export) - malloc"), 1);
	ft_strlcpy(key, cmd->argv[i], tmp - cmd->argv[i] + 1);
	value = ft_strdup(tmp + 1);
	if (!value)
		return (perror("minishell (ft_export) - malloc"), free(key), 1);
	return_value = env_set_key(key, value);
	free(key);
	free(value);
	return (return_value);
}
