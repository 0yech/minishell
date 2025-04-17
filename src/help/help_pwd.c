/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:34:36 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 14:55:56 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_pwd(void)
{
	printf(BOLD"MINISHELL - PWD\n"RESET);
	printf(BOLD"\tpwd - print the name of the current/working directory.\
\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\tpwd\t\tPrints PWD (current working directory).\n\n");
	printf(BOLD"EXAMPLES\n"RESET);
	printf("\tpwd\t\tPrints out /home/user/minishell\n");
	printf("\n");
}

void	help_pwd(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_pwd();
	ft_exit(NULL, 0);
}
