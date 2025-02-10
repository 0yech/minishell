/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:50:52 by estettle          #+#    #+#             */
/*   Updated: 2025/02/10 18:34:17 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (envclear(&head), NULL);
		new_node->next = NULL;
		if (!fill_env_node(envp[i], new_node))
			return (envdelone(new_node), envclear(&head), NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

t_env	*inienv(char **envp)
{
	t_env	*envcpy;

	envcpy = fill_envcpy(envp);
	return (envcpy);
}
