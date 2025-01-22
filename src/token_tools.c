/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:55:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/22 14:45:23 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *token_new(char *token)
{
	t_token *new_token;

	new_token = malloc(sizeof(*new_token));
	if (!new_token)
		return (NULL);
	new_token->value = token;
	new_token->next = NULL;
	return (new_token);
}

t_token *token_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next && ft_printf("Token_last loop cycle\n"))
		list = list->next;
	return (list);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token *last;

	if (!new)
		return ;
	last = token_last(*list);
	if (!last)
		*list = new;
	else
		last->next = new;
}

void	token_add_front(t_token **list, t_token *new)
{
	new->next = *list;
	*list = new;
}

void	tokens_clear(t_token **list)
{
	t_token *next_token;

	if (!list)
		return ;
	while (*list)
	{
		next_token = (*list)->next;
		free(*list);
		*list = next_token;
	}
	*list = NULL;
	free(list);
}