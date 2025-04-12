/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:44:15 by nrey              #+#    #+#             */
/*   Updated: 2025/04/12 06:02:25 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// No access to system("clear") gg

void	print_void_lines(int amount)
{
	if (amount <= 0)
		return ;
	while (amount--)
		printf("\n");
}

static void	print_man(void)
{
	printf(BOLD"MINISHELL\n"RESET);
	printf(BOLD"\ta minimal Unix shell made at 42 School.\n\n"RESET);
	printf(BOLD"BUILTINS\n"RESET);
	printf(UNDER"\techo"RESET"\t\tDisplay a line of text\n");
	printf(UNDER"\tcd"RESET"\t\tChange the current directory\n");
	printf(UNDER"\tpwd"RESET"\t\tPrint current working directory\n");
	printf(UNDER"\texport"RESET"\t\tSet environment variables\n");
	printf(UNDER"\tunset"RESET"\t\tRemove environment variables\n");
	printf(UNDER"\tenv"RESET"\t\tDisplay the environment\n");
	printf(UNDER"\texit"RESET"\t\tExit the shell\n\n");
	printf(BOLD"FEATURES\n"RESET);
	printf("\t- Relative and aboslute path command execution.\n");
	printf("\t- Quote handling (' and \").\n");
	printf("\t- Pipes, redirections and heredoc support.\n");
	printf("\t- Variable expansion ($VAR).\n");
	printf("\t- Proper signal handling (ctrl-C, ctrl-D, ctrl-\\).\n");
	printf("\t- Proper return values.\n\n");
	printf(BOLD"EXTRAS\n"RESET);
	printf("\t- '_' In env returns latest argument like bash.\n");
	printf("\t- Error messages and syntax errors to mimic bash.\n");
	printf("\t- Git support in prompt.\n\n");
	ft_exit(0);
}

void	print_help_header(void)
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
	print_void_lines(2);
}

static void	help_man(void)
{
	print_void_lines(50);
	print_help_header();
	print_man();
	ft_exit(0);
}

void	help_menu(int argc, char **argv)
{
	if (argc > 1 && (ft_strncmp(argv[1], "--h", 4) == 0
			|| ft_strncmp(argv[1], "--H", 4) == 0))
	{
		if (argc == 2)
			help_man();
		else if (argc > 2)
		{
			if (ft_strncmp(argv[2], "echo", 5) == 0)
				help_echo();
			else if (ft_strncmp(argv[2], "cd", 3) == 0)
				help_cd();
			else if (ft_strncmp(argv[2], "export", 7) == 0)
				help_export();
			else if (ft_strncmp(argv[2], "env", 4) == 0)
				help_env();
			else if (ft_strncmp(argv[2], "exit", 5) == 0)
				help_exit();
			else if (ft_strncmp(argv[2], "unset", 6) == 0)
				help_unset();
			else if (ft_strncmp(argv[2], "pwd", 4) == 0)
				help_pwd();
		}
		printf("minishell help usage : ./minishell --h [BUILTIN]\n");
		ft_exit(0);
	}
}
