/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/28 17:22:43 by cheyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_arraysize(char **p)
{
	int i;

	i = 0;
	while (p[i])
		i++;
	return (i);
}

void	ft_export(char *value)
{
	char *var;
	char **check;

	check = ft_split(value, '=');
	if (check == NULL)
		return ;
	if (ft_arraysize(check) == 1)
	{
		var = getenv(value);
		if (var == NULL)
			return ;
	}
	else if (ft_arraysize(check) == 2)
	{
		var = getenv(check[0]);
	}	
	else
	{
		free_array(check);
	}
}