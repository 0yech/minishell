/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/04/10 13:44:33 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compares the env token given in argument with the list of tokens also
 * passed as argument, and returns the next token in alphabetical order,
 * starting from the minimum token.
 * If NULL is passed as the minimum, returns the lowest ranked token.
 */
static t_env	*find_lowest_str(t_env *lst, t_env *min)
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
	while (i--)
	{
		tmp = find_lowest_str(env, tmp);
		if (tmp->name)
			if (write(STDOUT_FILENO, "export ", 8) == -1
				|| write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name)) == -1)
				return (perror("minishell (export_print) - write"), 0);
		if (tmp->value && tmp->value[0])
			if (write(STDOUT_FILENO, "=\"", 2) == -1
				|| write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value)) == -1
				|| write(STDOUT_FILENO, "\"", 1) == -1)
				return (perror("minishell (export_print) - write"), 0);
		if (write(STDOUT_FILENO, "\n", 2) == -1)
			return (perror("minishell (export_print) - write"), 0);
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
	char	*tmp;
	char	*key;
	char	*value;

	if (!str)
		return (export_print());
	tmp = ft_strchr(str, '=');
	if (!tmp)
	{
		if (env_set_key(str, NULL) == -1)
			return (-1);
		return (0);
	}
	if (tmp - ft_strchr(str, '+') == 1)
		return (export_concat(str));
	key = malloc(tmp - str + 1);
	if (!key)
		return (perror("minishell (ft_export) - malloc"), -1);
	ft_strlcpy(key, str, tmp - str + 1);
	value = ft_strdup(tmp + 1);
	if (!value)
		return (perror("minishell (ft_export) - malloc"), free(key), -1);
	if (env_set_key(key, value) == -1)
		return (free(key), free(value), -1);
	return (free(key), free(value), 0);
}
