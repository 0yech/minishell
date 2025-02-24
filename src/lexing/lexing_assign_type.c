/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_assign_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:15:21 by nrey              #+#    #+#             */
/*   Updated: 2025/02/24 22:01:50 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_varassign_syntax(char *str)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(str);
	while (str[i] != '=' && i < size)
	{
		if (i == 0)
			if (ft_isdigit(str[i]))
				return (0);
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	if (str[i] == '=' && i == size - 1)
		return (0);
	if (str[i] == '=' && i < size)
		return (VARASSIGN);
	return (0);
}

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
		if ((token->prev->type == REDIRECT_FILE
				&& token->prev->prev->prev == NULL)
			|| token->prev->type == VARASSIGN)
			return (COMMAND);
		if (token->prev->type == REDIRECT_IN
			|| token->prev->type == REDIRECT_OUT)
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
		if (!type)
			type = valid_varassign_syntax(current->value);
		if (type)
			current->type = type;
		else
			current->type = look_for_command_type(current);
		printf("\nNode value : %s\n", current->value);
		printf("Node type : %d\n", current->type);
		current = current->next;
	}
}
