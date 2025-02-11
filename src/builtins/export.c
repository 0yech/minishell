/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/11 14:42:39 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return 0 if everything went well, 1 if an error occured.
 */
int	ft_export(char *str)
{
	char	**slices;

	if (!str)
	{
		ft_env();
		return (0);
	}
	if (ft_strchr(str, '='))
	{
        slices = ft_split(str, '=');
		if (env_set(slices[0], slices[1]) == 2)
			return (1);
	}
	else if (env_set(str, NULL) == 2)
        return (1);
	return (0);
}
