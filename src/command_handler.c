/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/03 20:56:27 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list)
{
	// TODO Need to take into account int return values of builtins
	// printf("%s\n", (*token_list)->value);
	if (!ft_strncmp((*token_list)->value, "exit", ft_strlen((*token_list)->value)))
		ft_exit(token_list);
	if (!ft_strncmp((*token_list)->value, "pwd", ft_strlen((*token_list)->value)))
		ft_pwd();
	if (!ft_strncmp((*token_list)->value, "cd", ft_strlen((*token_list)->value)))
		ft_cd(token_list);
	if (!ft_strncmp((*token_list)->value, "env", ft_strlen((*token_list)->value)))
		ft_env();
	if (!ft_strncmp((*token_list)->value, "export", ft_strlen((*token_list)->value)))
	{
		if ((*token_list)->next)
			ft_export((*token_list)->next->value);
		else
			ft_export(NULL);
	}
	if (!ft_strncmp((*token_list)->value, "unset", ft_strlen((*token_list)->value)))
	{
		if ((*token_list)->next)
			ft_unset((*token_list)->next->value);
		else
			printf("unset : not enough arguments\n"); // Probably something better to do here (perror?)
	}
	t_command *cmd = parsing_handler(token_list);
	free_command_list(cmd);
}
