/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/19 10:54:04 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	history_handler(char *input)
{
	if (!input || !*input)
		return ;
	add_history(input);
}

static int	get_next_token(t_token **token_list, char *input)
{
	int	i;


}

static t_token	**create_tokens(char *input)
{
	t_token	**token_list;
	int		total_progress;

	token_list = ft_calloc(sizeof(t_token *), 1);
	total_progress = 0;
	if (!token_list)
		return (NULL);
	while (*(input + total_progress))
	{
		total_progress += get_next_token(token_list, input + total_progress);
	}
	return (token_list);
}

t_token	**init_token_list(char *input)
{
	t_token	**token_list;

	history_handler(input);
	token_list = create_tokens(input);
	if (!token_list)
		return (NULL);
	/*
	prompt = ft_split(input, ' ');
	if (prompt == NULL)
		return (NULL);
	if (prompt[0] == NULL)
		return (free(prompt), free(token_list), NULL);
	i = 0;
	while (prompt[i])
		token_add_back(token_list, token_new(prompt[i++]));
	free(prompt[i]); // Free only last element, the rest is used in tokens
	free(prompt);
	*/
	return (token_list);
}
