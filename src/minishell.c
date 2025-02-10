/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/02/10 18:36:01 by nrey             ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_token	**token_list;
	t_env	*env;
	char	*input;
	char	cwd[1024];

	(void)argc, (void)argv;
	while (TRUE)
	{
		printf("%s ", getcwd(cwd, sizeof(cwd)));\
		env = inienv(envp);
		input = readline(":3 $>");
		token_list = init_token_list(input);
		free(input);
		if (token_list == NULL)
			continue ;
		command_handler(token_list, env);
		tokens_clear(token_list);
		envclear(&env);
	}
}
