/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:01 by estettle          #+#    #+#             */
/*   Updated: 2025/02/20 15:42:56 by estettle         ###   ########.fr       */
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
