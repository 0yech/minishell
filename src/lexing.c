/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/19 22:51:25 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**init_token_list(char **tokens)
{
	t_token	**token_list;

	token_list = malloc(sizeof(t_token *));
	if (!token_list)
		return NULL;
	*token_list = NULL;
	while (tokens && *tokens) // infinite loop here, works fine when debugging but not in standard exec??
	{
		ft_printf("init_token_list loop cycle\n");
		token_add_back(token_list, token_new(*tokens));
		tokens++;
	}
	return (token_list);
}
