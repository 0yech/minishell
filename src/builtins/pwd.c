/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:14:41 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/21 20:00:56 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell (ft_pwd) - getcwd");
		return (1);
	}
	if (write(STDOUT_FILENO, pwd, ft_strlen(pwd)) == -1)
		return (free(pwd), perror("minishell (ft_pwd) - write"), -1);
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return (free(pwd), perror("minishell (ft_pwd) - write"), -1);
	free(pwd);
	return (0);
}
