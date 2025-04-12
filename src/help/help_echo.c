/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 03:21:18 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 05:58:42 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_echo(void)
{
	printf(BOLD"MINISHELL - ECHO\n"RESET);
	printf(BOLD"\techo - display a line of text.\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\techo"RESET" [STRING]\t\tDisplays a line of text.\n");
	printf("\techo "BOLD"-n"RESET" [STRING]\t");
	printf("Displays a line of text "BOLD"without a new line"RESET".\n\n");
	printf(BOLD"FEATURES\n"RESET);
	printf("\t- Quote handling (' and \")\n");
	printf("\t- Handles env variable enxpansions properly.\n\n");
	printf(BOLD"EXAMPLES\n"RESET);
	printf("\techo \"$PATH\"\t\tWill print the content of the $PATH variable.");
	printf("\n");
	printf("\techo '\"$PATH\"'\t\tWill print \"$PATH\"\
(surrounded by double quotes).\n");
	printf("\n");
}

void	help_echo(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_echo();
	ft_exit(0);
}
