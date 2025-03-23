/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:01 by estettle          #+#    #+#             */
/*   Updated: 2025/03/23 21:59:19 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FIXME: echo '"$PATH '$USER'"' has two spaces between the vars instead of one
// FIXME: echo "'"$PATH" $USER'" messes up the quotes (starts with ' and ends with ")

/**
 * @brief A quote or single quote is considered "valid" if it is at the end or
 * at the beginning of a token, as in followed or preceded by whitespace.
 */
bool is_valid_quote(char* str, int index)
{
	if (!str || !str[index])
		return (false);
	if ((str[index] == '\'' || str[index] == '"')
		&& ((index == 0
				|| (!ft_isprint(str[index - 1])
					|| str[index - 1] == ' '))
			|| (!ft_isprint(str[index + 1])
				|| str[index + 1] == ' ')
		)
	)
		return (true);
	return (false);
}

/**
 * @brief Goes through a string given as input and returns the index that
 * ends the token contained within, checking for valid quotes along the way.
 * This is just the delimiting the token part, cleaning the quotes comes after.
 *
 * @see quotes_clean
 */
int	quotes_handler(char *start)
{
	int		i;
	char	quote_kind;

	i = 0;
	while (start[i] != '"' && start[i] != '\'')
		i++;
	quote_kind = start[i];
	i++;
	while (start[i] && (start[i] != quote_kind || !is_valid_quote(start, i)))
		i++;
	if (start[i] == quote_kind)
		i++;
	return (i);
}

/**
 * @brief This function cleans a token of any unnecessary quotes (trailing,
 * preceding or even contained inside.
 *
 * @param raw_token The token still wrapped in quotes.
 * @return A cleaned version of the token. NULL if an error occurred.
 */
char	*quotes_clean(char *raw_token)
{
	char	quotes_kind;
	char	*clean_token;
	int		i;
	int		j;

	if (!raw_token)
		return (NULL);
	i = 0;
	while (raw_token[i] && raw_token[i] != '"' && raw_token[i] != '\'')
		i++;
	if (raw_token[i] != '"' && raw_token[i] != '\'')
		return (raw_token);
	quotes_kind = raw_token[i];
	clean_token = ft_calloc(ft_strlen(raw_token), sizeof(char));
	if (!clean_token)
		return (perror("minishell (quotes_clean) - ft_calloc"),
			free(raw_token), NULL);
	i = 0;
	j = -1;
	while (raw_token[++j])
		if (raw_token[j] != quotes_kind)
			clean_token[i++] = raw_token[j];
	clean_token[i] = 0;
	free(raw_token);
	return (clean_token);
}
