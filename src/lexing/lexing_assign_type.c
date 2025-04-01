/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_assign_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:15:21 by nrey              #+#    #+#             */
/*   Updated: 2025/03/17 10:41:35 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks a given string and determines if it is part of standard
 * minishell operations : pipes, redirections or heredocs.
 *
 * @return The operation found, or 0 if the string isn't one.
 */
int	look_for_operations(char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (PIPE);
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (REDIRECT_IN);
	if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (REDIRECT_OUT);
	if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (HEREDOC);
	return (0);
}

/**
 * @brief Returns the type of a given token.
 * 
 * @details The end of the function only returns an argument if no command has
 * been found in that token group yet (a group being separated by pipes).
 * This prevents cases like < Makefile less giving less a type of ARGUMENT.
 * 
 * @param token The token to analyze.
 * @param current_has_cmd A bool keeping track of if the current command has
 * been found
 * @return int The t_token_type of the token.
 */
int	look_for_command_type(t_token *token, bool current_has_cmd)
{
	if (token->prev == NULL)
		return (COMMAND);
	if (token->prev->type == REDIRECT_FILE
		&& token->prev->prev->prev == NULL)
		return (COMMAND);
	if (token->prev->type == REDIRECT_IN
		|| token->prev->type == REDIRECT_OUT
		|| token->prev->type == APPEND)
		return (REDIRECT_FILE);
	if (token->prev->type == HEREDOC)
		return (DELIM);
	if (token->prev->type == PIPE)
		return (COMMAND);
	if ((token->prev->type == COMMAND || token->prev->type == OPTION)
		&& ft_strncmp(token->value, "-", 1) == 0
		&& ft_strlen(token->value) > 1)
		return (OPTION);
	if (token->prev->type == COMMAND)
		return (ARGUMENT);
	if (current_has_cmd)
		return (ARGUMENT);
	return (COMMAND);
}

void	assign_types(t_token **token_list)
{
	t_token	*current;
	bool	current_has_cmd;
	int		type;

	if (!token_list || !(*token_list))
		return ;
	current = *token_list;
	while (current)
	{
		current_has_cmd = false;
		type = look_for_operations(current->value);
		if (type)
			current->type = type;
		else
			current->type = look_for_command_type(current, current_has_cmd);
		printf("\nNode value : %s\n", current->value);
		printf("Node type : %d\n", current->type);
		current = current->next;
	}
}
