/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:08:56 by estettle          #+#    #+#             */
/*   Updated: 2025/03/14 10:04:57 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strjoin_equals(char *s1, char *s2)
{
	char	*out;
	int		len;
	int		len2;
	int		finallen;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	finallen = len + len2 + 2;
	out = malloc(finallen);
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1, finallen);
	out[len] = '=';
	ft_strlcpy(out + len + 1, s2, finallen - len - 1);
	return (out);
}

int	env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// TODO: why does this exist?
char	**env_to_char(t_env *env)
{
	char	**envtab;
	t_env	*tmp;
	int		i;

	i = 0;
	envtab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envtab)
		return (NULL);
	tmp = env;
	while (i < env_size(env))
	{
		if (!tmp->name || !tmp->value)
			envtab[i] = NULL;
		else
		{
			envtab[i] = strjoin_equals(tmp->name, tmp->value);
			if (!envtab[i])
				free_array(envtab);
		}
		i++;
		tmp = tmp->next;
	}
	envtab[i] = NULL;
	return (envtab);
}

/**
 * @brief Searches through the environment of the shell for a node matching the
 * provided key.
 *
 * @param key The key string to look up.
 * @return A pointer to the env node containing the key we're searching for. If
 * no node was found containing it, return the last node of the environment.
 */
// TODO: redo nomenclature around get_key, env_set, env_get etc etc
t_env	*env_get_key(char *key)
{
	t_env	*tmp;

	if (!key || !*key)
		return (NULL);
	tmp = *env_get();
	while (tmp)
	{
		if (ft_strlen(key) == ft_strlen(tmp->name)
			&& ft_strncmp(key, tmp->name, ft_strlen(key)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	// printf("minishell (get_key): %s is not set!\n", key);
	return (NULL);
}
