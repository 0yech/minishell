/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:31:57 by estettle          #+#    #+#             */
/*   Updated: 2025/03/01 13:37:59 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Refactor this function to not use a malloc, we don't really need one
char	*get_variable(char *str)
{
	size_t	i;
	char	*key;
	char	*raw_var;
	char	*var;

	key = ft_calloc(ft_strlen(str), sizeof(char));
	if (!key)
		return (NULL);
	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	ft_strlcpy(key, str, i + 1);
	raw_var = get_key(key)->value;
	if (!raw_var)
		return (NULL);
	var = ft_strchr(raw_var, '=');
	if (!var)
		return (NULL);
	free(key);
	return (var);
}

int	full_token_size(char *raw_token)
{
	char	*var;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (raw_token[i])
	{
		if (raw_token[i] == '$')
		{
			i++;
			var = get_variable(raw_token + i);
			if (var)
				size += ft_strlen(var);
			while (ft_isprint(raw_token[i]) && raw_token[i] != ' ')
				i++;
		}
		size++;
		i++;
	}
	return (size);
}

char	*var_expand(char *token)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	*expanded_token;

	expanded_token = ft_calloc(full_token_size(token), sizeof(char));
	if (!expanded_token)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$' && get_variable(token + i + 1))
		{
			var = get_variable(token + i + 1);
			ft_strlcpy(expanded_token + j, var, ft_strlen(var));
			j += ft_strlen(var);
			i++;
			while (ft_isalnum(token[i]))
				i++;
		}
		expanded_token[j++] = token[i++];
	}
	free(token);
	return (expanded_token);
}