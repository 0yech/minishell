/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:21:02 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 05:57:07 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_unset(void)
{
	printf(BOLD"MINISHELL - UNSET\n"RESET);
	printf(BOLD"\tunset - destroy variables and their values.\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\tunset"RESET" [VAR]\t\tUnsets the given variable from the \
shell environment.\n\n");
	printf(BOLD"EXAMPLES\n"RESET);
	printf("\texport\tHELLO=123\tCreating a var, \
"BOLD"read \"./minishell --h export\""RESET"\n");
	printf("\tunset\tHELLO\t\tDestroying the $HELLO variabel if it exists.\n");
	printf("\n");
}

void	help_unset(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_unset();
	ft_exit(NULL, 0);
}
