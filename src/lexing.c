/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/22 14:45:01 by estettle         ###   ########.fr       */
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
	while (tokens && *tokens)
		token_add_back(token_list, token_new(*(tokens++)));
	return (token_list);
}
