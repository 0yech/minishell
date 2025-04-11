/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:44:15 by nrey              #+#    #+#             */
/*   Updated: 2025/04/11 16:58:15 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// No access to system("clear") gg

static void	print_void(int amount)
{
	if (amount <= 0)
		return ;
	while (amount--)
		printf("\n");
}

static void	print_man(void)
{
	printf(BOLD"MINISHELL\n"RESET);
	printf(BOLD"\ta minimal Unix shell made at 42 School\n\n"RESET);
	printf(BOLD"BUILTINS\n"RESET);
	printf(UNDER"\techo"RESET"\t\tDisplay a line of text\n");
	printf(UNDER"\tcd"RESET"\t\tChange the current directory\n");
	printf(UNDER"\tpwd"RESET"\t\tPrint current working directory\n");
	printf(UNDER"\texport"RESET"\t\tSet environment variables\n");
	printf(UNDER"\tunset"RESET"\t\tRemove environment variables\n");
	printf(UNDER"\tenv"RESET"\t\tDisplay the environment\n");
	printf(UNDER"\texit"RESET"\t\tExit the shell\n\n");
	printf(BOLD"FEATURES\n"RESET);
	printf("\t- Quote handling (' and \")\n");
	printf("\t- Pipes, redirections and heredoc support\n");
	printf("\t- Variable expansion ($VAR)\n");
	printf("\t- Proper signal handling (ctrl-C, ctrl-\\)\n");
	printf("\t- Proper return values\n\n");
	printf(BOLD"EXTRAS\n"RESET);
	printf("\t- '_' In env returns latest argument like bash\n");
	printf("\t- Git support in prompt\n");
	printf("\t- Error messages and syntax errors to mimic bash\n\n");
}

static void	print_help(void)
{
	printf("   __  ___ _        _       __        __ __\n");
	printf("  /  |/  /(_)___   (_)___  / /  ___  / // /\t\t"LIME"nrey\t\t \
		(0yech)"RESET"\n");
	printf(" / /|_/ // // _ \\ / /(_-< / _ \\/ -_)/ // / \t\t"BOLD ORG"estettle\t \
		(Aisling Fontaine)"RESET"\n");
	printf("/_/  /_//_//_//_//_//___//_//_/\\__//_//_/  \t\t"BLUE \
		"42 Lausanne"RESET"\n");
	printf("____________________________________________\n\n"RESET);
	printf(YELLOW"https://github.com/0yech/minishell"RESET);
	print_void(2);
	print_man();
	ft_exit(0);
}

void	help_menu(int argc, char **argv)
{
	if (argc > 1 && (ft_strncmp(argv[1], "--h", 4) == 0
			|| ft_strncmp(argv[1], "--H", 4) == 0))
	{
		print_void(50);
		print_help();
	}
	return ;
}
