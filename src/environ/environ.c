/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:50:52 by estettle          #+#    #+#             */
/*   Updated: 2025/03/12 18:41:18 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**env_get(void)
{
	static t_env	*env;

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
			return (perror("minishell (fill_envcpy) - ft_calloc"),
				env_clear(&head), NULL);
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
	t_env	*shlvl;
	char	*new_shlvl;

	envcpy = env_get();
	*envcpy = fill_envcpy(envp);
	shlvl = env_get_key("SHLVL");
	if (shlvl && shlvl->value)
	{
		new_shlvl = ft_itoa(ft_atoi(shlvl->value) + 1);
		if (!new_shlvl)
			perror("minishell (env_init) - ft_itoa");
		env_set_key("SHLVL", new_shlvl);
		free(new_shlvl);
	}
	else
		env_set_key("SHLVL", "1");
}
