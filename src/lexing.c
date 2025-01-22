/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/01/22 20:22:43 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**init_token_list(char *input)
{
	char	**prompt;
	t_token	**token_list;

	token_list = malloc(sizeof(t_token *));
	prompt = ft_split(input, ' ');
	if (prompt == NULL || prompt[0] == NULL)
		return (NULL);
	if (!token_list)
		return (NULL);
	*token_list = NULL;
	while (prompt && *prompt)
		token_add_back(token_list, token_new(*(prompt++)));
	free_array(prompt);
	return (token_list);
}
