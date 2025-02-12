/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/12 14:56:31 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return 0 if everything went well, 1 if an error occurred.
 */
int	ft_export(char *str)
{
	char	**slices;

	if (!str)
	{
		ft_env(); // Need to write the exported values with export beforehand
		return (0);
	}
	if (ft_strchr(str, '='))
	{
		slices = ft_split(str, '=');
		if (!slices[1])
			return (printf("[!] - Invalid identifier!\n"), free_array(slices), 1);
		if (env_set(slices[0], slices[1]) == 2)
			return (free_array(slices), 1);
		free(slices[2]);
		free(slices);
	}
	else
		return (printf("[!] - Export without = isn't supported yet!\n"), 1);
	return (0);
}
