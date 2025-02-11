/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:50:52 by estettle          #+#    #+#             */
/*   Updated: 2025/02/11 17:44:49 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**env_get(void)
{
	static t_env *env;

	return (&env);
}

/**
 * @brief Copies envp environment data into a linked list for future reuse and
 * updating in the shell.
 *
 * @param envp The environment as passed to the main() function.
 * @return A pointer to the head of the linked list just created.
 */
t_env	*fill_envcpy(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = NULL;
	current = NULL;
	while (*envp)
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (!new_node)
			return (env_clear(&head), NULL);
		if (!env_fill_node(*envp, new_node))
			return (env_delone(new_node), env_clear(&head), NULL);
		if (!head)
			head = new_node;
		else
		{
			current->next = new_node;
			new_node->prev = current;
		}
		current = new_node;
		envp++;
	}
	return (head);
}

/**
 * @brief Initializes the environment of the shell.
 *
 * @param envp The environment as passed to the main() function.
 * @return A pointer to the head of the linked list just created.
 */
void	env_init(char **envp)
{
	t_env	**envcpy;

	envcpy = env_get();
	*envcpy = fill_envcpy(envp);
}
