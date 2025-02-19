/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/18 15:26:54 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	history_handler(char *input)
{
	if (!input || !*input)
		return ;
	add_history(input);
}

t_token	**init_token_list(char *input)
{
	int		i;
	char	**prompt;
	t_token	**token_list;

	token_list = malloc(sizeof(t_token *));
	if (!token_list)
		return (NULL);
	*token_list = NULL;
	history_handler(input);
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
	return (token_list);
}
