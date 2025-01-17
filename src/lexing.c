/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/17 17:52:17 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**init_token_list(char **tokens)
{
	t_token	**token_list;

	token_list = malloc(sizeof(t_token *));
	if (!token_list)
		return NULL;
	while (*tokens)
	{
		token_add_back(token_list, token_new(*tokens));
		tokens++;
	}
	return (token_list);
}
