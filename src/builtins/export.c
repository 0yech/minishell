/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/04/07 21:36:07 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : export wa= should export wa="", which should appear on env, unlike vars called without '='

/**
 * @brief Compares the env token given in argument with the list of tokens also
 * passed as argument, and returns the next token in alphabetical order,
 * starting from the minimum token.
 * If NULL is passed as the minimum, returns the lowest ranked token.
 */
static t_env	*find_lowest_str(t_env *list, t_env *minimum)
{
	t_env	*lowest;

	if (minimum)
		while (ft_strncmp(list->name, minimum->name, ft_strlen(list->name) + 1) <= 0)
			list = list->next;
	lowest = list;
	while (list)
	{
		if (minimum)
		{
			if (ft_strncmp(list->name, lowest->name, ft_strlen(list->name) + 1) < 0
				&& ft_strncmp(list->name, minimum->name, ft_strlen(list->name) + 1) > 0)
				lowest = list;
		}
		else if ((ft_strncmp(list->name, lowest->name, ft_strlen(list->name) + 1) < 0))
			lowest = list;
		list = list->next;
	}
	return (lowest);
}

/**
 * @brief Prints all exported variables to stdout formatted as
 * export <key>="<value>".
 * 
 * @return 0 if all went well, -1 if an error occurred.
 */
int	export_print(void)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	env = *env_get();
	if (!env)
		return (-1);
	tmp = NULL;
	i = env_size(env);
	while (i)
	{
		tmp = find_lowest_str(env, tmp);
		if (write(STDOUT_FILENO, "export ", 8) == -1
			|| write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name)) == -1
			|| write(STDOUT_FILENO, "=\"", 2) == -1
			|| write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value)) == -1
			|| write(STDOUT_FILENO, "\"\n", 2) == -1)
			return (perror("minishell (export_print) - write"), 0);
		i--;
	}
	return (0);
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

/**
 * @brief Helper method of the export builtin for concatenation of env variables
 * with new values. Example : export PATH+=/home
 */
int	export_concat(char *str)
{
	t_env	*var;
	char	*concat_str;
	char	**slices;

	slices = ft_split(str, '+');
	if (!slices)
		return (perror("minishell (export_concat) - ft_split"), -1);
	if (slices[0][0] == '=')
		return (printf("export: Wrong syntax!\n"), free_array(slices), -1);
	var = env_get_key(slices[0]);
	concat_str = ft_calloc(export_concat_size(var, slices[1]), sizeof(char));
	if (!concat_str)
		return (perror("minishell (export_concat) - ft_calloc"),
			free_array(slices), -1);
	if (var && var->value)
	{
		ft_strlcpy(concat_str, var->value, ft_strlen(var->value) + 1);
		ft_strlcpy(concat_str + ft_strlen(var->value),
			slices[1] + 1, ft_strlen(slices[1]) + 1);
	}
	else
		ft_strlcpy(concat_str, slices[1] + 1, ft_strlen(slices[1]));
	if (env_set_key(slices[0], concat_str) == -1)
		return (free_array(slices), free(concat_str), -1);
	return (free_array(slices), free(concat_str), 0);
}

/**
 * @return 0 if everything went well, -1 if an error occurred.
 */
int	ft_export(char *str)
{
	char	**slices;

	if (!str)
		return (export_print());
	if (ft_strchr(str, '='))
	{
		if (ft_strchr(str, '=') - ft_strchr(str, '+') == 1)
			return (export_concat(str));
		slices = ft_split(str, '=');
		if (!slices)
			return (perror("minishell (ft_export) - ft_split"), -1);
		if (!slices[1])
			return (printf("minishell (ft_export): Invalid identifier!\n"),
				free_array(slices), -1);
		if (env_set_key(slices[0], slices[1]) == -1)
			return (free_array(slices), -1);
		free_array(slices);
	}
	else if (env_set_key(str, str) == -1)
		return (-1);
	return (0);
}
