/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:19 by nrey              #+#    #+#             */
/*   Updated: 2025/03/02 12:48:18 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fill node command
// Function to return OPTIONS/ARGUMENTS as char **args, ends with NULL
// Function to count pipes/commands x
// Function to fill EACH command, and advance to the next one. x

// while cmd -> fill fds args per command

void	fill_args_fds(t_command *cmd, t_token *token)
{
	t_command *current;
	
	current = cmd;

    while (token)
    {
        if (token->type == PIPE)
            current = current->next;
        else if (token->type == REDIRECT_IN && token->next
			&& token->next->type == REDIRECT_FILE) // <
                current->fdio->input = ft_strdup(token->next->value);
        else if (token->type == REDIRECT_OUT && token->next
			&& token->next->type == REDIRECT_FILE) // >
                current->fdio->output = ft_strdup(token->next->value);
        else if (token->type == APPEND && token->next
			&& token->next->type == REDIRECT_FILE) // >>
        {
                current->fdio->output = ft_strdup(token->next->value);
                current->fdio->fdout = O_WRONLY | O_CREAT | O_APPEND;
        }
        token = token->next;
    }
}

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
		printf("Input fdio : %s\n", cmd->fdio->input);
		printf("output fdio : %s\n\n", cmd->fdio->output);
        printf("Command : %s\n", cmd->command);
        while (cmd->argv[i])
		{
            printf("argv%d : %s\n", i, cmd->argv[i]);
			i++;
		}
		i = 0;
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
	cmd->fdio = malloc(sizeof(t_fd));
	if (!cmd->fdio)
		return (NULL);
	ft_memset(cmd->fdio, 0, sizeof(t_fd));
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
	//t_env		**env;
	//char		**waos;

	command_list = parse_commands(*token_list);
	fill_args_fds(command_list, *token_list);
	//print_commands(command_list);
	//env = env_get();
	//waos = env_to_char(*env);
	//printf("%s", waos[1]);
	//free_array(waos);
	return (command_list);
}