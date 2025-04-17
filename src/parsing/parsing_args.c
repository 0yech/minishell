/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:08 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/17 19:46:29 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @brief Takes a token as argument and counts the number of options and
* arguments contained within, then returns it.
*
* @details Starts at 1 to include the command name as well.
*/
static int	count_argsopt(t_token **args)
{
	int	count;

	count = 1;
	while (*args && (*args)->type != PIPE)
	{
		if ((*args)->type == OPTION || (*args)->type == ARGUMENT)
			count++;
		args++;
	}
	return (count);
}

static int	count_args(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		i++;
		token = token->next;
	}
	return (i);
}

/**
 * @brief Converts the arguments of a command in an array argv, ready to be
 * passed to execve.
 * 
 * @param args The array of tokens contained within a command.
 * @return An array of strings argv.
 */
char	**args_to_argv(t_token **args)
{
	size_t	i;
	char	**argv;

	argv = ft_calloc(count_argsopt(args) + 1, sizeof(char *));
	if (!argv)
		return (perror("minishell (args_to_argv) - malloc"), NULL);
	i = 0;
	while (*args && (*args)->type != PIPE)
	{
		if (i == 0 || (*args)->type == OPTION || (*args)->type == ARGUMENT)
		{
			argv[i] = ft_strdup((*args)->value);
			if (!argv[i])
			{
				perror("minishell (extract_args) - ft_strdup");
				while (i > 0)
					free(argv[--i]);
				return (free(argv), NULL);
			}
			i++;
		}
		args++;
	}
	argv[i] = NULL;
	return (argv);
}

static	t_token	**duplicate_args(t_token *token, int arg_count)
{
	t_token	**args;
	int		i;

	args = ft_calloc(arg_count + 1, sizeof(t_token *));
	if (!args)
		return (perror("minishell (duplicate_args) - malloc"), NULL);
	i = 0;
	while (i < arg_count && token)
	{
		args[i] = token_new(ft_strdup(token->value));
		if (!args[i] || !args[i]->value)
		{
			perror("minishell (duplicate_args) - malloc/token_new");
			while (--i >= 0)
			{
				free(args[i]->value);
				free(args[i]);
			}
			free(args);
			return (NULL);
		}
		args[i]->type = token->type;
		args[i++]->quoted = token->quoted;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

/**
* @brief Extracts all tokens until a pipe or the end of the list
* and returns them as an array.
*
* @param token The token to start from in the list.
* @return An array of tokens containing all tokens for a single command.
*/

t_token	**extract_args(t_token *token)
{
	int	arg_count;

	arg_count = count_args(token);
	return (duplicate_args(token, arg_count));
}
