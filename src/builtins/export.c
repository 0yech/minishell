/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/17 14:52:58 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all exported variables to stdout formatted as "export <var>".
 * @return 0 if all went well, -1 if an error occurred.
 */
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
		slices = ft_split(str, '=');
		if (!slices)
			return (perror("minishell (ft_export) - ft_split"), -1);
		if (!slices[1])
			return (printf("[!] - Invalid identifier!\n"), free_array(slices), -1);
		if (env_set_key(slices[0], slices[1]) == -1)
			return (free_array(slices), -1);
		free_array(slices);
	}
	else
	{
		if (env_set_key(str, str) == -1)
			return (-1);
	}
	return (0);
}
