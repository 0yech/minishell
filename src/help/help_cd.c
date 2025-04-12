/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 03:54:12 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 05:57:18 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_man_cd(void)
{
	printf(BOLD"MINISHELL - CD\n"RESET);
	printf(BOLD"\tcd - change the working directory.\n\n"RESET);
	printf(BOLD"USAGE\n"RESET);
	printf("\tcd"RESET" [NEW PATH]\t\tChanges cwd to the wanted path.\n\n");
	printf(BOLD"EXAMPLES\n"RESET);
	printf("\tcd ..\t\t\tWill move to the parent directory.\n");
	printf("\tcd src\t\t\tWill move to the ./src folder, if it exists.\n");
	printf("\tcd -\t\t\tWill move to $OLDPWD, the previous pwd.\n");
	printf("\tcd ~\t\t\tWill move to /home\n");
	printf("\tcd\t\t\tWill also move to /home\n");
	printf("\n");
}

void	help_cd(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_cd();
	ft_exit(0);
}
