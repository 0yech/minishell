/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_expand_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:31:57 by estettle          #+#    #+#             */
/*   Updated: 2025/02/27 18:15:19 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	full_token_size(char *raw_token)
{
	return (0);
}

char	*get_variable(char *str)
{
	return (0);
}

char	*var_expand(char *raw_token)
{
	int		i;
	char	*expanded_token;
	char	*variable;

	if (!raw_token)
		return (NULL);
	expanded_token = ft_calloc(
		ft_strlen(raw_token) + full_token_size(raw_token) + 1, 1);
	if (!expanded_token)
		return (free(raw_token), NULL);
	i = 0;
	while (raw_token[i])
	{
		if (raw_token[i] == '\'')
		{
			i++;
			while (raw_token[i] != '\'')
				i++;
		}
		if (raw_token[i] == '$')
		{
			variable = get_variable(raw_token + i);
			ft_strlcpy(raw_token + i, variable, ft_strlen(variable));
			free(variable);
		}
		i++;
	}
	free(raw_token);
	return (expanded_token);
}