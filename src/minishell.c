/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/03/07 04:59:50 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Don't worry we'll put this function elsewhere than here */
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !array[i])
		return ;
	while (array[i])
		free(array[i++]);
	free(array[i]);
	free(array);
}

// TODO : Add non interactive mode
int	main(int argc, char **argv, char **envp)
{
	t_token	**token_list;
	char	*input;

	(void)argc, (void)argv;
	signal_handler();
	env_init(envp);
	while (TRUE)
	{
		display_prompt();
		input = readline(":3 $>");
		if (!input)
			ft_exit(0);
		token_list = init_token_list(input);
		free(input);
		if (token_list == NULL)
			continue ;
		if (*token_list == NULL)
		{
			free(token_list);
			continue ;
		}
		print_tokens(*token_list);
		command_handler(token_list);
		tokens_clear(token_list);
	}
}
