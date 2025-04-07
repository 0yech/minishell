/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <firefoxSpinnie@protonmail.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:08:56 by estettle          #+#    #+#             */
/*   Updated: 2025/04/07 21:16:40 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the given double char pointer.
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !array[i])
		return ;
	while (array[i])
		free(array[i++]);
	free(array[i]);
	free(array);
}

/**
 * @brief Joins two strings together with a '=' inbetween and the second string
 * wrapped in double quotes, if it exists. Used for env to char ** conversion.
 */
static char	*strjoin_equals(char *s1, char *s2)
{
	char		*out;
	size_t		len;
	size_t		len2;
	size_t		final_len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	final_len = len + len2 + 2;
	out = malloc(final_len);
	if (!out)
		return (perror("minishell (strjoin_equals) - malloc"), NULL);
	ft_strlcpy(out, s1, final_len);
	out[len] = '=';
	ft_strlcpy(out + len + 1, s2, final_len - len - 1);
	return (out);
}

/**
 * @brief Calculates the number of variables contained in the environment.
 */
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

/**
 * @brief Formats the environment linked list as a malloced double char pointer,
 * and returns it.
 *
 * @param env A pointer to the first environment node of the linked list.
 * @return A double char pointer containing the environment line by line.
 */
char	**env_to_char(t_env *env)
{
	char	**envtab;
	t_env	*tmp;
	int		i;

	i = 0;
	envtab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envtab)
		return (perror("minishell (env_to_char) - malloc"), NULL);
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
