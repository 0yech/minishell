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
int	count_argsopt(t_token *token)
{
	int	count;

	count = 1;
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION || token->type == ARGUMENT)
			count++;
		token = token->next;
	}
	return (count);
}

char	**args_to_argv(t_token *arg)
{
	size_t	i;
	char	**argv;

	argv = ft_calloc(count_argsopt(arg) + 1, sizeof(char *));
	if (!argv)
		return (perror("minishell (args_to_argv) - malloc"), NULL);
	i = 0;
	while (arg && arg->type != PIPE)
	{
		if (i == 0 || arg->type == OPTION || arg->type == ARGUMENT)
		{
			argv[i] = ft_strdup(arg->value);
			if (!argv[i])
			{
				perror("minishell (extract_args) - ft_strdup");
				while (i > 0)
					free(argv[--i]);
				return (free(argv), NULL);
			}
			i++;
		}
		arg = arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * @brief Extracts arguments and options from a given token.
 *
 * @param token The token to analyze.
 * @return A double char pointer containing a string for each argument / option.
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
