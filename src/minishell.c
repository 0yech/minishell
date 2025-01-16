/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:48 by estettle          #+#    #+#             */
/*   Updated: 2025/01/16 23:14:24 by cheyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline(":3 $>");
		if (!ft_strncmp(str, "exit", 4))
		{
			free(str);
			exit(0);
		}
		ft_printf("%s\n", str);
		free(str);
	}
}
