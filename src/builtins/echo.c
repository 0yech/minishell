/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:49:19 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/11 17:00:35 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	char	**tmp;
	int		nl;

	nl = 1;
	tmp = cmd->argv + 1;
	if (cmd->arguments[1]->type == OPTION
		&& ft_strncmp(*tmp, "-n", ft_strlen(*tmp) + 1) == 0)
		nl = 0;
	if (*tmp && *tmp + 1 && nl == 0)
		tmp++;
	while (*tmp)
	{
		if (write(STDOUT_FILENO, *tmp, ft_strlen(*tmp)) == -1)
			return (perror("minishell (ft_echo) - write"), -1);
		if (*(tmp + 1))
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (perror("minishell (ft_echo) - write"), -1);
		tmp++;
	}
	if (nl == 1)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("minishell (ft_echo) - write"), -1);
	}
	return (0);
}
