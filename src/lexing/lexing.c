/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/25 12:08:35 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isolate_token(char *input)
{
	int		i;
	char	special_char;

	i = 0;
	if (!input)
		return (i);
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
	{
		special_char = input[i];
		if (input[i + 1] == special_char && input[i] != '|')
			return (i + 2);
		return (i + 1);
	}
	while (input[i] && ft_isprint(input[i]) && input[i] != ' '
		&& !(input[i] == '|' || input[i] == '>' || input[i] == '<'))
	{
		if (input[i] == '"' || input[i] == '\'')
			return (quotes_handler(input));
		i++;
	}
	return (i);
}

static int	get_next_token(t_token **token_list, char *input)
{
	t_token	*new;
	char	*substr;
	int		i;

	new = token_new(NULL);
	if (!new)
		return (-1);
	i = isolate_token(input);
	substr = var_expand(ft_substr(input, 0, i));
	if (!substr)
		return (free(new), -1);
	new->value = quotes_clean(new, substr);
	free(substr);
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
		return (perror("minishell (create_token) - malloc"), NULL);
	tot_progress = 0;
	while (*(input + tot_progress) && (!ft_isprint(*(input + tot_progress))
			|| *(input + tot_progress) == ' '))
		tot_progress++;
	while (input[tot_progress])
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

	if (input && *input)
		add_history(input);
	token_list = create_tokens(input);
	if (!token_list)
		return (NULL);
	assign_types(token_list);
	return (token_list);
}
