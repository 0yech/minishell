/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:31:57 by estettle          #+#    #+#             */
/*   Updated: 2025/03/21 16:12:13 by estettle         ###   ########.fr       */
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
	char	*key;
	t_env	*var;

	i = 0;
	while (ft_isprint(str[i]) && str[i] != '"'
		&& str[i] != '\'' && str[i] != ' ')
		i++;
	key = ft_calloc(i + 1, sizeof(char));
	if (!key)
		return (perror("minishell (get_variable) - ft_calloc"), NULL);
	ft_strlcpy(key, str, i + 1);
	var = env_get_key(key);
	if (!var || !(var->value))
		return (free(key), NULL);
	free(key);
	return (var->value);
}

/**
 * @brief Takes a raw_token as an input and returns its length with all
 * variables contained within expanded.
 */
size_t	full_token_size(char *token)
{
	char	*var;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	if (!token)
		return (0);
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			var = get_variable(token + i);
			if (var)
				size += ft_strlen(var);
			while (token[i] && ft_isprint(token[i])
				&& token[i] != '"' && token[i] != '\'' && token[i] != ' ')
				i++;
		}
		size++;
		if (token[i])
			i++;
	}
	return (size);
}

/**
 * @brief Is called when a $ is found in the token. Searches for the variable
 * and copies it if it does exist, otherwise copies nothing and moves on.
 */
void	handle_var(char *token, char *expanded_token, size_t *i, size_t *j)
{
	char	*var;

	(*i)++;
	var = get_variable(token + *i);
	if (var)
	{
		ft_strlcpy(expanded_token + *j, var, ft_strlen(var) + 1);
		*j += ft_strlen(var);
	}
	while (ft_isprint(token[*i]) && token[*i] != '"'
		&& token[*i] != '\'' && token[*i] != ' ')
		(*i)++;
}

/**
 * @brief Takes a token as an argument and returns the same token with all
 * variables contained expanded. Valid variables that exist in the environment
 * are expanded to their values, while variables that don't exist are expanded
 * to "", an empty string.
 */
char	*var_expand(char *token)
{
	size_t	i;
	size_t	j;
	char	*expanded_token;

	expanded_token = ft_calloc(full_token_size(token) + 1, sizeof(char));
	if (!expanded_token)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$')
			handle_var(token, expanded_token, &i, &j);
		else
			expanded_token[j++] = token[i++];
	}
	expanded_token[j] = 0;
	return (free(token), expanded_token);
}
