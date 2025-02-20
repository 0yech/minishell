/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_assign_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:15:21 by nrey              #+#    #+#             */
/*   Updated: 2025/02/20 16:01:10 by nrey             ###   ########.fr       */
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
	return (0); // NOT an operation
}

int	valid_command_type(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0
		|| ft_strncmp(str, "cd", ft_strlen(str)) == 0
		|| ft_strncmp(str, "pwd", ft_strlen(str)) == 0
		|| ft_strncmp(str, "export", ft_strlen(str)) == 0
		|| ft_strncmp(str, "unset", ft_strlen(str)) == 0
		|| ft_strncmp(str, "env", ft_strlen(str)) == 0
		|| ft_strncmp(str, "exit", ft_strlen(str)) == 0
		|| ft_strncmp(str, "grep", ft_strlen(str)) == 0
		|| ft_strncmp(str, "ls", ft_strlen(str)) == 0)
		return (0);
	return (1); // NOT a command
}

int	look_for_command_type(t_token *token)
{
	if (token->prev == NULL && valid_command_type(token->value) == 0)
		return (COMMAND);
	else if (token->prev != NULL)
	{
		if (token->prev->type == PIPE
			&& valid_command_type(token->value) == 0)
			return (COMMAND);
		if (token->prev->type == COMMAND
			&& valid_command_type(token->value) == 0)
			return (ARGUMENT);
		if (token->prev->type == COMMAND
			&& ft_strncmp(token->value, "-", 1) == 0)
			return (OPTION);
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
		//printf("\nNode value : %s\n", current->value);
		//printf("Node type : %d\n", current->type);
		current = current->next;
	}
}
