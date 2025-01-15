/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/01/15 18:45:45 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *str;
	char *ext = "exit";

	while (1)
	{
		str = readline(":3 $>");
		if (!ft_strncmp(str, ext, 5))
		{
			free(str);
			exit(0);
		}
		printf("%s\n", str);
		free(str);
	}
	
}