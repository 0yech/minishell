/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:36 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/28 15:42:29 by cheyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(t_token **token_list, char **envp)
{
	ft_printf("%s\n", (*token_list)->value);
	if (!ft_strncmp((*token_list)->value, "exit", 4))
		ft_exit(token_list);
	if (!ft_strncmp((*token_list)->value, "pwd", 3))
		ft_pwd();
	if (!ft_strncmp((*token_list)->value, "cd", 2))
		ft_cd(token_list);
	if (!ft_strncmp((*token_list)->value, "env", 3))
		ft_env(envp);
}
