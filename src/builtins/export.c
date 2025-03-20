/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/20 21:04:38 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all exported variables to stdout formatted as "export <var>".
 * @return 0 if all went well, -1 if an error occurred.
 */
// TODO: export_print should print exported values in alphabetical order
int	export_print(void)
{
	int		i;
	char	**env;

	env = env_to_char(*env_get());
	if (!env)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (write(STDOUT_FILENO, "export ", 8) == -1
			|| write(STDOUT_FILENO, env[i], ft_strlen(env[i])) == -1
			|| write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("minishell (export_print) - write"),
				free_array(env), 0);
		i++;
	}
	return (free_array(env), 0);
}

size_t	export_concat_size(t_env *var, char *new_value)
{
	size_t	tot_size;

	tot_size = ft_strlen(new_value);
	if (var && var->value)
		tot_size += ft_strlen(var->value);
	return (tot_size + 1);
}

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
