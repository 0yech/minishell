/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/02/20 15:41:30 by estettle         ###   ########.fr       */
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
	t_token	*new;
	int		i;

	i = 0;
	new = token_new(NULL);
	if (!new)
		return (-1);
	while (input && input[i] && ft_isprint(input[i]) && input[i] != ' ')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i = quotes_handler(input + i);
			break ;
		}
		i++;
	}
	new->value = ft_substr(input, 0, i);
	if (!new->value)
		return (free(new), -1);
	token_add_back(token_list, new);
	return (i);
}

static t_token	**create_tokens(char *input)
{
	t_token	**token_list;
	int		tot_progress;
	int		progress;

	token_list = ft_calloc(sizeof(t_token *), 1);
	if (!token_list)
		return (NULL);
	tot_progress = 0;
	while (*(input + tot_progress))
	{
		progress = get_next_token(token_list, input + tot_progress);
		if (progress < 0)
			return (tokens_clear(token_list), NULL);
		tot_progress += progress;
		while (*(input + tot_progress) && (!ft_isprint(*(input + tot_progress))
				|| *(input + tot_progress) == ' '))
			tot_progress++;
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
	assign_types(token_list);
	return (token_list);
}
