/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:39:44 by cheyo             #+#    #+#             */
/*   Updated: 2025/03/23 22:03:36 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_var(char *str)
{
	bool	is_in_double_quote;
	int		i;

	i = 0;
	is_in_double_quote = false;
	while (str[i])
	{
		if (str[i] == '"')
			is_in_double_quote = true;
		else if (str[i] == '\'' && !is_in_double_quote)
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '$')
			return (true);
		if (str[i])
			i++;
	}
	return (false);
}

static int	isolate_token(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (i);
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
	{
		if (input[i + 1] == '|' || input[i + 1] == '>' || input[i + 1] == '<')
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
	substr = ft_substr(input, 0, i);
	if (has_var(substr))
		new->value = quotes_clean(var_expand(substr));
	else
		new->value = quotes_clean(substr);
	if (!new->value)
		return (free(new), -1);
	return (token_add_back(token_list, new), i);
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

	add_history(input);
	token_list = create_tokens(input);
	if (!token_list)
		return (NULL);
	assign_types(token_list);
	return (token_list);
}
