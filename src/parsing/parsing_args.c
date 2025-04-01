/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:00:08 by estettle          #+#    #+#             */
/*   Updated: 2025/03/27 19:32:01 by estettle         ###   ########.fr       */
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

/**
 * @brief Extracts all tokens until a pipe or the end of the list
 * and returns them as an array.
 *
 * @param token The token to start from in the list.
 * @return An array of tokens containing all tokens for a single command.
 */
t_token	**extract_args(t_token *token)
{
	int		i;
	t_token	*tmp;
	t_token	**args;

	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		tmp = tmp->next;
		i++;
	}
	args = ft_calloc(i + 1, sizeof(t_token *));
	if (!args)
		return (perror("minishell (extract_args) - malloc"), NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		args[i] = token;
		i++;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}
