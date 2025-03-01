/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:31:57 by estettle          #+#    #+#             */
/*   Updated: 2025/03/01 11:41:14 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	full_token_size(char *raw_token)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (raw_token[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	*get_variable(char *str)
{
	char	*raw_var;
	char	*var;

	raw_var = get_key(str)->value;
	if (!raw_var)
		return (NULL);
	var = ft_strchr(raw_var, '=');
	if (!var)
		return (NULL);
	return (var);
}

char	*var_expand(char *token)
{
	int		i;
	char	*expanded_token;
	char	*variable;

	if (!token)
		return (NULL);
	expanded_token = malloc(full_token_size(token) + 1);
	if (!expanded_token)
		return (free(token), NULL);
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] != '\'')
				i++;
		}
		if (token[i] == '$')
		{
			variable = get_variable(token + i);
			if (variable == NULL)
			{
				i++;
				continue ;
			}
			ft_strlcpy(token + i, variable, ft_strlen(variable));
			free(variable);
		}
		i++;
	}
	free(token);
	return (expanded_token);
}