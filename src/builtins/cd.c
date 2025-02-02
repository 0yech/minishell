/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/01/24 15:49:11 by cheyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_token **token_list)
{
	if ((*token_list)->next == NULL)
	{
		if (chdir(getenv("HOME")) == 0)
			return (0);
		return (1);
	}
	if (chdir((*token_list)->next->value) == 0)
	{
		ft_printf("[!] - Switched working directory to %s\n",
			(*token_list)->next->value);
		return (0);
	}
	else
	{
		ft_printf("[!] - Failed to change working directory!\n");
		return (-1);
	}
}
