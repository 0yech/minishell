/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by fireinside        #+#    #+#             */
/*   Updated: 2025/03/25 11:49:32 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO (optional): In echo "<<", the << shouldn't be interpreted as a heredoc
// TODO: exec format error leaks a loooot (trying to launch ./launch.sh in minishell, for example)

int	main(int argc, char **argv, char **envp)
{
	t_token	**token_list;
	char	*input;

	help_menu(argc, argv);
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
	return (env_clear(env_get()), exit(0), 0);
}
