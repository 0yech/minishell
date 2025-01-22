/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/01/22 20:24:31 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Don't worry we'll put this function elsewhere than here */
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !(*array))
		return ;
	while (array[i])
		free(array[i++]);
	free(array[i]);
	free(array);
}

int	main(void)
{
	t_token	**token_list;
	char	*input;
	char	cwd[1024];

	while (TRUE)
	{
		ft_printf("%s ", getcwd(cwd, sizeof(cwd)));
		input = readline(":3 $>");
		token_list = init_token_list(input);
		if (token_list == NULL)
			continue ;
		ft_printf("%s\n", (*token_list)->value);
		if (!ft_strncmp((*token_list)->value, "exit", 4))
			ft_exit(token_list);
		tokens_clear(token_list);
	}
}
