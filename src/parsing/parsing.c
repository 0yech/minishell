/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:19 by nrey              #+#    #+#             */
/*   Updated: 2025/03/07 09:38:00 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_args_fds(t_command *cmd, t_token *token)
{
	t_command	*current;

	current = cmd;

	while (token)
	{
		if (token->type == PIPE)
		{
			if (current == NULL || current->next == NULL)
				return ;
			current = current->next;
		}
		else if (current && current->fdio)
		{
			if (token->type == REDIRECT_IN && token->next
				&& token->next->type == REDIRECT_FILE) // <
					current->fdio->input = ft_strdup(token->next->value);
			else if (token->type == REDIRECT_OUT && token->next
				&& token->next->type == REDIRECT_FILE) // >
					current->fdio->output = ft_strdup(token->next->value);
			else if (token->type == APPEND && token->next
				&& token->next->type == REDIRECT_FILE) // >>
			{
					current->fdio->output = ft_strdup(token->next->value); // TODO noticed this leaked
					current->fdio->fdout = O_WRONLY | O_CREAT | O_APPEND;
			}
			else if (token->type == HEREDOC && token->next
				&& token->next->type == DELIM)
					current->fdio->hd_delim = ft_strdup(token->next->value);
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
		printf("-----------------------------------------\n");
		printf("Input fdio : %s\n", cmd->fdio->input);
		printf("Heredoc_quotes : %d\n", cmd->fdio->hd_quotes);
		printf("hd_delim : %s\n", cmd->fdio->hd_delim);
		printf("fdin : %d\n", cmd->fdio->fdin);
		printf("fdout : %d\n", cmd->fdio->fdout);
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
	t_command   *command_list;
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
	return (command_list);
}