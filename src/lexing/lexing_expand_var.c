/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:31:57 by estettle          #+#    #+#             */
/*   Updated: 2025/03/03 10:11:48 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Searches the environment for the first word contained in str, and
 * returns its value as a pointer to the first character in the env.
 *
 * @param str A string starting with the variable name to be searched.
 * @return The value of the variable in the environment.
 */
char	*get_variable(char *str)
{
	size_t	i;
	char	key[9999];
	t_env	*var;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	ft_strlcpy(key, str, i + 1);
	var = get_key(key);
	if (!var || !(var->value))
		return (NULL);
	return (var->value);
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
			printf("%s\n", var);
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
			ft_strlcpy(expanded_token + j, var, ft_strlen(var) + 1);
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