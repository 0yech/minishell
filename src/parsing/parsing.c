/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:19 by nrey              #+#    #+#             */
/*   Updated: 2025/03/10 19:20:28 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("-----------------------------------------\n");
		printf("Input fdio : %s\n", cmd->fdio->input);
		printf("Heredoc_quotes : %d\n", cmd->fdio->hd_quotes);
		printf("hd_delim : %s\n", cmd->fdio->hd_delim);
		printf("fdin : %d\n", cmd->fdio->fdin);
		printf("fdout : %d\n", cmd->fdio->fdout);
		printf("output fdio : %s\n\n", cmd->fdio->output);
		printf("Command : %s\n", cmd->command);
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

t_command	*fill_parsing(t_token *token)
{
	t_command	*cmd;

	if (!token)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = ft_strdup(token->value);
	cmd->argv = extract_args(token);
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fdio = ft_calloc(1, sizeof(t_fd));
	if (!cmd->fdio)
		return (NULL);
	return (cmd);
}

t_command	*parse_commands(t_token *token)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;

	head = NULL;
	current = NULL;
	while (token)
	{
		if (token->type == COMMAND || (token->prev && token->prev->type == PIPE))
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

t_command	*parsing_handler(t_token **token_list)
{
	t_command	*command_list;
	//t_env		**env;
	//char		**waos;

	command_list = parse_commands(*token_list);
	if (valid_pipes(*token_list) == 1)
		return (free_command_list(command_list), NULL);
	fill_args_fds(command_list, *token_list);
	assign_pipes(command_list);
	process_heredoc(command_list);
	print_commands(command_list);
	//env = env_get();
	//waos = env_to_char(*env);
	//printf("%s", waos[1]);
	//free_array(waos);
	if (exec_checks(command_list) != 0)
		return(free_command_list(command_list), NULL);
	return (command_list);
}
