/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:50:52 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/16 17:35:44 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the environment of minishell.
 * 
 * @return A pointer to the first node of the environment.
 */
t_env	**env_get(void)
{
	static t_env	*env;

	return (&env);
}

/**
 * @brief Copies envp environment data into a linked list for future use and
 * updating in the shell.
 *
 * @param envp The environment as passed to the main function.
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
			return (perror("minishell (fill_envcpy) - malloc"),
				env_clear(&head), NULL);
		if (env_fill_node(*envp, new_node) == -1)
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
 * @details Copies envp into the minishell's environment list.
 * Also makes sure to increment SH_LVL by 1 after copying. If the variable
 * doesn't exist, then sets it to 1.
 * @param envp The environment as passed to the main() function as minishell
 * starts.
 */
void	env_init(char **envp)
{
	t_env	**envcpy;
	t_env	*shlvl;
	char	*new_shlvl;
	char	cwd[999];

	envcpy = env_get();
	*envcpy = fill_envcpy(envp);
	shlvl = env_get_key("SHLVL");
	if (shlvl && shlvl->value)
	{
		new_shlvl = ft_itoa(ft_atoi(shlvl->value) + 1);
		if (!new_shlvl)
			perror("minishell (env_init) - ft_itoa");
		if (env_set_key("SHLVL", new_shlvl) == 1)
			printf("minishell (env_init): failed to set SHLVL!\n");
		free(new_shlvl);
	}
	else if (env_set_key("SHLVL", "1") == 1)
		printf("minishell (env_init): failed to set SHLVL!\n");
	if (getcwd(cwd, 999) == NULL)
		perror("minishell (env_init) - getcwd");
	env_set_key("PWD", cwd);
}
