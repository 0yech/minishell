/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:01 by fireinside        #+#    #+#             */
/*   Updated: 2025/03/24 12:17:19 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Goes through a string given as input and returns the index that
 * ends the token contained within, handling quotes accordingly.
 * This is just the delimiting the token part, cleaning the quotes comes after.
 *
 * @see quotes_clean
 */
int	quotes_handler(char *str)
{
	int		i;
	char	quote_kind;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && ft_isprint(str[i]) && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_kind = str[i++];
			while (str[i] && str[i] != quote_kind)
				i++;
		}
		if (str[i])
			i++;
	}
	return (i);
}

/**
 * @brief This function cleans a token of any unnecessary quotes (trailing,
 * or preceding).
 *
 * @param token Sets token->quoted to true if a quote was found in the token.
 * @param raw_token The token still wrapped in quotes. Assumed to be a
 * pointer to a valid string.
 * @return A cleaned version of the token. NULL if an error occurred.
 */
char	*quotes_clean(t_token *token, char *raw_token)
{
	char	quotes_kind;
	char	*clean_token;
	int		i;

	clean_token = ft_calloc(ft_strlen(raw_token) + 1, sizeof(char));
	if (!clean_token)
		return (perror("minishell (quotes_clean) - malloc"), NULL);
	i = 0;
	while (*raw_token)
	{
		if (*raw_token == '\'' || *raw_token == '"')
		{
			token->quoted = true;
			quotes_kind = *(raw_token++);
			while (*raw_token && *raw_token != quotes_kind)
				clean_token[i++] = *(raw_token++);
			if (*raw_token)
				raw_token++;
			continue ;
		}
		if (*raw_token)
			clean_token[i++] = *(raw_token++);
	}
	clean_token[i] = 0;
	return (clean_token);
}
