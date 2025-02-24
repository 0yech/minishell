/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:01 by estettle          #+#    #+#             */
/*   Updated: 2025/02/24 16:02:30 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief A quote or single quote is considered "valid" if it is at the end or
 * at the beginning of a token, as in followed or preceded by whitespace.
 */
t_bool	is_valid_quote(char *str, int index)
{
	if (!str || !str[index])
		return (FALSE);
	if ((str[index] == '\'' || str[index] == '"')
		&& ((index == 0
				|| (!ft_isprint(str[index - 1])
					|| str[index - 1] == ' '))
			|| (!ft_isprint(str[index + 1])
				|| str[index + 1] == ' ')
			)
		)
	{
		return (TRUE);
	}
	return (FALSE);
}

int	quotes_handler(char *start)
{
	int	i;

	// Here's the plan : copy the token containing all quotes and then clean them
	// to get a clean token to be used
	// Valid quotes delimiting a token must be either preceded by whitespace to open
	// or followed by whitespace to close
	i = 0;
	if (start[i] == '"')
	{
		i++;
		while (start[i] && !is_valid_quote(start, i))
			i++;
		if (start[i] == '"')
			i++;
	}
	else if (start[i] == '\'')
	{
		i++;
		while (start[i] && !is_valid_quote(start, i))
			i++;
		if (start[i] == '\'')
			i++;
	}
	return (i);
}

/**
 * @brief This function cleans a token of any unnecessary quotes (trailing,
 * preceding or even contained inside.
 *
 * @param raw_token The token still wrapped in quotes.
 * @return A cleaned version of the token.
 */
char	*quotes_clean(char *raw_token)
{
	char	quotes_kind;
	char	*clean_token;
	int		i;
	int		j;

	if (!raw_token)
		return (NULL);
	if (raw_token[0] != '"' && raw_token[0] != '\'')
		return (free(raw_token), NULL);
	quotes_kind = raw_token[0];
	clean_token = ft_calloc(ft_strlen(raw_token) - 1, sizeof(char));
	if (!clean_token)
		return (free(raw_token), NULL);
	i = 0;
	j = 0;
	while (raw_token[j])
	{
		if (raw_token[j] != quotes_kind)
			clean_token[i++] = raw_token[j];
		j++;
	}
	clean_token[i] = 0;
	return (free(raw_token), clean_token);
}
