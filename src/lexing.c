/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/28 10:23:43 by estettle         ###   ########.fr       */
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
	history_handler(input);
	prompt = ft_split(input, ' ');
	if (prompt == NULL || prompt[0] == NULL)
		return (NULL);
	if (!token_list)
		return (NULL);
	*token_list = NULL;
	i = 0;
	while (prompt[i])
		token_add_back(token_list, token_new(prompt[i++]));
	free(prompt[i]);
	free(prompt);
	return (token_list);
}
