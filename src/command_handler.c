/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/11 17:56:36 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list)
{
	// Need to take into account int return values of builtins
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
	if (!ft_strncmp((*token_list)->value, "unset", 5))
	{
		if ((*token_list)->next)
			ft_unset((*token_list)->next->value);
		else
			printf("unset : not enough arguments\n"); // Probably something better to do here (perror?)
	}
}
