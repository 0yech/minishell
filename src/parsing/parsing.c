/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:19 by nrey              #+#    #+#             */
/*   Updated: 2025/02/26 00:08:45 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fill node command
// Function to return OPTIONS/ARGUMENTS as char **args, ends with NULL
// Function to count pipes/commands x
// Function to fill EACH command, and advance to the next one. x

int count_argsopt(t_token *token)
{
    int count = 0;
    while (token && token->type != PIPE)
    {
        if (token->type == OPTION || token->type == ARGUMENT)
            count++;
        token = token->next;
    }
    return count;
}

void print_commands(t_command *cmd)
{
	int i;

	i = 0;
    while (cmd)
    {
        printf("Command : %s\n", cmd->command);
        while (cmd->argv[i])
		{
            printf("argv%d : %s\n", i, cmd->argv[i]);
			i++;
		}
		printf("\n");
        cmd = cmd->next;
    }
}

char	**extract_args(t_token *token)
{
	int count;
	int i;
	char **args;

	i = 0;
	count = count_argsopt(token);
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (free(args), NULL);
	args[i++] = ft_strdup(token->value);
	token = token->next;
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION || token->type == ARGUMENT)
		{
			args[i] = ft_strdup(token->value);
			if (!args[i])
			{
				while (i > 0)
					free(args[--i]);
				return (free(args), NULL);
			}
			i++;		
		}
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

t_command *fill_parsing(t_token *token)
{
	t_command	*cmd;

	if (!token || token->type != COMMAND)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = ft_strdup(token->value);
	cmd->argv = extract_args(token);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_command	*parse_commands(t_token *token)
{
	t_command *head;
	t_command *current;
	t_command *new_cmd;

	head = NULL;
	current = NULL;
	while (token)
	{
		if (token->type == COMMAND)
		{
			new_cmd = fill_parsing(token);
			if (!new_cmd)
				return (NULL);
			if (!head)
				head = new_cmd;
			else
			{
				current->next = new_cmd;
				new_cmd->prev = current;
			}
			current = new_cmd;
		}
		token = token->next;
	}
	return (head);
}

t_command *parsing_handler(t_token **token_list)
{
	t_command   *command_list;

	command_list = parse_commands(*token_list);
	print_commands(command_list);
	return (command_list);
}