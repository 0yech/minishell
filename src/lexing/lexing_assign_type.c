/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_assign_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:15:21 by nrey              #+#    #+#             */
/*   Updated: 2025/02/28 04:01:06 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_for_operations(char *str)
{
	if (!str)
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
		return (DELIM);
	return (0); // NOT an operation
}

int	look_for_command_type(t_token *token)
{
	if (token->prev == NULL)
		return (COMMAND);
	else if (token->prev != NULL)
	{
		if (token->prev->type == REDIRECT_FILE
				&& token->prev->prev->prev == NULL)
			return (COMMAND);
		if (token->prev->type == REDIRECT_IN
			|| token->prev->type == REDIRECT_OUT 
			|| token->prev->type == APPEND)
			return (REDIRECT_FILE);
		if (token->prev->type == PIPE)
			return (COMMAND);
		if (token->prev->type == COMMAND
			&& ft_strncmp(token->value, "-", 1) == 0
			&& ft_strlen(token->value) > 1)
			return (OPTION);
		if (token->prev->type == COMMAND)
			return (ARGUMENT);
		else
			return (ARGUMENT);
	}
	return (0);
}

void	assign_types(t_token **token_list)
{
	t_token	*current;
	int		type;

	if (!token_list || !(*token_list))
		return ;
	current = *token_list;
	while (current)
	{
		type = look_for_operations(current->value);
		if (type)
			current->type = type;
		else
			current->type = look_for_command_type(current);
		printf("\nNode value : %s\n", current->value);
		printf("Node type : %d\n", current->type);
		current = current->next;
	}
}
