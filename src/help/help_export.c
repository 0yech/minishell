/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:12:21 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 05:56:26 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_export(void)
{
	printf(BOLD"MINISHELL - EXPORT\n"RESET);
	printf(BOLD"\texport - set the export attribute for variables.\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\texport [VAR]\t\tCreates an environment variable.\n");
	printf("\texport [VAR]=[VALUE]\tCreates an environment variable\
 with a given value.\n");
	printf("\texport [VAR]+=[VALUE]\tConcatenates the new value to\
 the old one.\n\n");
	printf(BOLD"EXAMPLES\n"RESET);
	printf("\texport PRICE\t\tWill create a variable named $PRICE.\n");
	printf("\texport PRICE=200\tCreates price if it doesn't exist\n\t\t\t\t\
and sets it's value to 200.\n");
	printf("\texport PRICE+=100\tThe value of $PRICE is now \"200100\".\n");
	printf("\n");
}

void	help_export(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_export();
	ft_exit(0);
}
