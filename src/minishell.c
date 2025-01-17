/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/01/17 14:59:19 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	**prompt;

	while (TRUE)
	{
		prompt = ft_split(readline(":3 $>"), ' ');

		if (!ft_strncmp(prompt[0], "exit", 4))
		{
			free(prompt);
			exit(0);
		}
		else if (!ft_strncmp(prompt[0], "cd", 2))
			ft_cd(prompt[1]);
		// ft_printf("%s\n", prompt[0]);
		free(prompt); // WEEHOOWEEHOO LEAKS OVER HERE (need to free individual tokens)
	}
}
