/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:49:29 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 05:56:09 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_env(void)
{
	printf(BOLD"MINISHELL - ENV\n"RESET);
	printf(BOLD"\tenv - print all set environment variables.\
 (specific to minishell)\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\tenv\t\tLists all exported variables with set values.\n \
\t\t\tVariables without values will therefore not appear.\n");
	printf("\n");
}

void	help_env(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_env();
	ft_exit(NULL, 0);
}
