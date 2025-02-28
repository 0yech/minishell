/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:31:57 by estettle          #+#    #+#             */
/*   Updated: 2025/02/28 16:25:37 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	full_token_size(char *raw_token)
{
	(void)raw_token;
	return (0);
}

char	*get_variable(char *str)
{
	(void)str;
	return (0);
}

char	*var_expand(char *token)
{
	int		i;
	char	*expanded_token;
	char	*variable;

	if (!token)
		return (NULL);
	expanded_token = malloc(ft_strlen(token) + full_token_size(token) + 1);
	if (!expanded_token)
		return (free(token), NULL);
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && ++i)
			while (token[i] != '\'')
				i++;
		if (token[i] == '$')
		{
			variable = get_variable(token + i);
			ft_strlcpy(token + i, variable, ft_strlen(variable));
			free(variable);
		}
		i++;
	}
	free(token);
	return (expanded_token);
}