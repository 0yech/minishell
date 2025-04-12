/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:59:42 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 15:03:03 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_exit(void)
{
	printf(BOLD"MINISHELL - EXIT\n"RESET);
	printf(BOLD"\texit - ensure normal process termination.\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\texit"RESET" [STATUS]\t\tEnds minishell with the given \
return value.\n");
	printf("\texit\t\t\tEnds minishell with the default return status of 0");
	printf("\n\n");
	printf(BOLD"FEATURES\n"RESET);
	printf("\t- exit's status updates $?, a variable corresponding to the \
most recent return value.\n\n");
	printf("\n");
}

void	help_exit(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_exit();
	ft_exit(0);
}
