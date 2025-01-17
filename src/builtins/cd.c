/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:47:25 by estettle          #+#    #+#             */
/*   Updated: 2025/01/17 14:54:50 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path)
{
	if (chdir(path) == 0)
	{
		ft_printf("[!] - Switched working directory to %s\n", path);
		return (0);
	}
	else
	{
		ft_printf("[!] - Failed to change working directory!\n");
		return (-1);
	}
}