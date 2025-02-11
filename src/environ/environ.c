/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:50:52 by estettle          #+#    #+#             */
/*   Updated: 2025/02/11 12:04:44 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_env(void)
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
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (!new_node)
			return (env_clear(&head), NULL);
		if (!fill_env_node(envp[i], new_node))
			return (env_delone(new_node), env_clear(&head), NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
/*
int	env_add(char *key, char *value)
{

}
*/
/**
 * @brief Initializes the environment of the shell.
 *
 * @param envp The environment as passed to the main() function.
 * @return A pointer to the head of the linked list just created.
 */
void	env_init(char **envp)
{
	t_env	**envcpy;

	envcpy = get_env();
	*envcpy = fill_envcpy(envp);
}
