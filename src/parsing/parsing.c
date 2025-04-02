/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:19 by nrey              #+#    #+#             */
/*   Updated: 2025/03/27 19:16:34 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("-----------------------------------------\n");
		printf("fdin : %d\n", cmd->fdio->fdin);
		printf("fdout : %d\n", cmd->fdio->fdout);
		printf("Command : %s\n", cmd->command);
		i = 0;
		while (cmd->arguments[i])
		{
			printf("argument%d : %s\n", i, cmd->arguments[i]->value);
			i++;
		}
		printf("\n");
		i = 0;
		while (cmd->argv[i])
		{
			printf("argv%d : %s\n", i, cmd->argv[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}

/**
 * @brief Takes a token as argument and creates a command node with tokens
 * including and following the token argument.
 * 
 * @return A new command node containing all relevant tokens as arguments,
 * a valid list of argv, a calloced fdio and a command string, if there's one.
 */
static t_command	*fill_parsing(t_token *token)
{
	t_command	*cmd;

	if (!token)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (perror("minishell (fill_parsing) - malloc"), NULL);
	cmd->arguments = extract_args(token);
	if (!cmd->arguments)
		return (free(cmd->command), free(cmd), NULL);
	cmd->argv = args_to_argv(cmd->arguments);
	if (!cmd->argv)
		return (free(cmd->command), free(cmd), NULL);
	cmd->fdio = ft_calloc(1, sizeof(t_io));
	if (!cmd->fdio)
		return (perror("minishell (fill_parsing) - malloc"),
			free(cmd->command), free(cmd), NULL);
	
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
	{
		cmd->command = ft_strdup(token->value);
		if (!cmd->command)
			return (perror("minishell (fill_parsing) - malloc"),
				free(cmd), NULL);
	}
	return (cmd);
}

/**
 * @brief Loops through the list of lexer tokens given as argument and returns
 * a new list of parsed commands.
 * 
 * @details Command nodes are created by separating the tokens by the ones
 * having a type of PIPE. In effect, this means the number of commands output by
 * this function is the number of pipes contained, plus one.
 */
static t_command	*parse_commands(t_token *token)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;

	head = NULL;
	while (token)
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
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->next)
			token = token->next;
	}
	return (head);
}

t_command	*parsing_handler(t_token **token_list)
{
	t_command	*command_list;

	command_list = parse_commands(*token_list);
	if (valid_pipes(*token_list) == 1)
		return (free_command_list(command_list), NULL);
	assign_pipes(command_list);
	print_commands(command_list);
	if (exec_checks(command_list) != 0)
	{
		exec_update_env(command_list, 127);
		return (free_command_list(command_list), NULL);
	}
	return (command_list);
}
