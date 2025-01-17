/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/01/17 17:29:24 by cheyo            ###   ########.fr       */
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
	free(array);
}

int	main(void)
{
	char	**prompt;
	char	*input;
	char	cwd[1024];

	while (TRUE)
	{
		ft_printf("%s ", getcwd(cwd, sizeof(cwd)));
		input = readline(":3 $>");
		prompt = ft_split(input, ' ');
		if (prompt == NULL || prompt[0] == NULL)
			;
		
		else if (!ft_strncmp(prompt[0], "exit", 4))
		{
			free(prompt);
			exit(0);
		}
		else if (!ft_strncmp(prompt[0], "cd", 2))
			ft_cd(prompt[1]);
		free_array(prompt);
	}
}
