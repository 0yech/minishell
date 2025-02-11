/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/11 14:06:44 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list)
{
	printf("%s\n", (*token_list)->value);
	if (!ft_strncmp((*token_list)->value, "exit", 4))
		ft_exit(token_list);
	if (!ft_strncmp((*token_list)->value, "pwd", 3))
		ft_pwd();
	if (!ft_strncmp((*token_list)->value, "cd", 2))
		ft_cd(token_list);
	if (!ft_strncmp((*token_list)->value, "env", 3))
		ft_env();
	if (!ft_strncmp((*token_list)->value, "export", 6))
	{
		if ((*token_list)->next)
			ft_export((*token_list)->next->value);
        else
            ft_export(NULL);
	}
}
