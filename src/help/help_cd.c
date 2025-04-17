/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 03:54:12 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 15:02:45 by fireinside       ###   ########.fr       */
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
	printf("\tcd -\t\t\tWill move to $OLDPWD, the previous directory.\n");
	printf("\tcd ~\t\t\tWill move to /home\n");
	printf("\tcd\t\t\tWill also move to /home\n");
	printf("\n");
}

void	help_cd(void)
{
	print_void_lines(50);
	print_help_header();
	print_man_cd();
	ft_exit(NULL, 0);
}
