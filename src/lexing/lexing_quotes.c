/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:01 by estettle          #+#    #+#             */
/*   Updated: 2025/02/24 10:58:04 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (start[i] && start[i] != '"')
			i++;
		if (start[i] == '"')
			i++;
	}
	else if (start[i] == '\'')
	{
		i++;
		while (start[i] && start[i] != '\'')
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
	// char	quotes_kind;
	char	*clean_token;

	if (!raw_token || !raw_token[0])
		return (NULL);
	/* Quotes cleaning inside of token to be implemented
	quotes_kind = raw_token[0];
	if (quotes_kind != '\'' && quotes_kind != '"')
		return (NULL);
	*/
	clean_token = ft_substr(raw_token, 1, ft_strlen(raw_token) - 2);
	free(raw_token);
	if (!clean_token)
		return (NULL);
	return (clean_token);
}
