/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/03/25 11:49:32 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : Add non interactive mode
// TODO : add more error codes like "unexpected token near '<', so more checks"
// TODO : try to close all fds at exit

int	main(int argc, char **argv, char **envp)
{
	t_token	**token_list;
	char	*input;

	(void)argc, (void)argv;
	signal_handler();
	env_init(envp);
	while (true)
	{
		display_prompt();
		input = readline(":3 $>");
		if (!input)
			break ;
		token_list = init_token_list(input);
		free(input);
		if (token_list == NULL)
			continue ;
		if (*token_list == NULL)
		{
			free(token_list);
			continue ;
		}
		command_handler(token_list);
	}
	ft_exit(0);
}
