/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:55:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/04/17 19:30:20 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (perror("minishell (token_new) - malloc"), NULL);
	new_token->value = token;
	return (new_token);
}

t_token	*token_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	last = token_last(*list);
	if (!last)
		*list = new;
	else
	{
		last->next = new;
		new->prev = last;
	}
}

void	token_add_front(t_token **list, t_token *new)
{
	new->next = *list;
	*list = new;
}

void	tokens_clear(t_token **list)
{
	t_token	*next_token;
	t_token	*tmp;

	if (!list || !*list)
		return ;
	tmp = *list;
	while (tmp)
	{
		next_token = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next_token;
	}
	*list = NULL;
}
