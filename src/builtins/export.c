/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/25 11:56:07 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compares the string given in argument with the array of strings also
 * passed as argument, and returns the next string in alphabetical order,
 * starting from the given string.
 * If NULL is passed as the single string, returns the lowest ranked string.
 */
char	*find_lowest_str(char **array, char *minimum)
{
	size_t		i;
	char		*lowest;

	i = 0;
	if (minimum)
		while (ft_strncmp(array[i], minimum, ft_strlen(array[i]) + 1) <= 0)
			i++;
	lowest = array[i];
	while (array[i])
	{
		if (minimum)
		{
			if (ft_strncmp(array[i], lowest, ft_strlen(array[i]) + 1) < 0
				&& ft_strncmp(array[i], minimum, ft_strlen(array[i]) + 1) > 0)
				lowest = array[i];
		}
		else if ((ft_strncmp(array[i], lowest, ft_strlen(array[i]) + 1) < 0))
			lowest = array[i];
		i++;
	}
	return (lowest);
}

/**
 * @brief Prints all exported variables to stdout formatted as "export <var>".
 * @return 0 if all went well, -1 if an error occurred.
 */
int	export_print(void)
{
	int		i;
	char	**env;
	char	*tmp;

	env = env_to_char(*env_get());
	if (!env)
		return (-1);
	tmp = NULL;
	i = env_size(*env_get());
	while (i)
	{
		tmp = find_lowest_str(env, tmp);
		if (write(STDOUT_FILENO, "export ", 8) == -1
			|| write(STDOUT_FILENO, tmp, ft_strlen(tmp)) == -1
			|| write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("minishell (export_print) - write"),
				free_array(env), 0);
		i--;
	}
	return (free_array(env), 0);
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
