/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fireinside <aisling.fontaine@pm.me>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:28:50 by cheyo             #+#    #+#             */
/*   Updated: 2025/04/16 20:12:20 by fireinside       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all exported variables to stdout formatted as
 * export <key>="<value>".
 * 
 * @return 0 if all went well, -1 if an error occurred.
 */
int	export_print(void)
{
	int		i;
	t_env	*tmp;

	if (!(*env_get()))
		return (-1);
	tmp = NULL;
	i = env_size(*env_get());
	while (i--)
	{
		tmp = find_lowest_str(*env_get(), tmp);
		if (ft_strncmp(tmp->name, "_", 2) == 0
			|| ft_strncmp(tmp->name, "?", 2) == 0)
			continue ;
		if (tmp->name && (write(STDOUT_FILENO, "export ", 7) == -1
				|| write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name)) == -1))
			return (perror("minishell (export_print) - write"), 0);
		if (tmp->value && (write(STDOUT_FILENO, "=\"", 2) == -1
				|| write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value)) == -1
				|| write(STDOUT_FILENO, "\"", 1) == -1))
			return (perror("minishell (export_print) - write"), 0);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("minishell (export_print) - write"), 0);
	}
	return (0);
}

/**
 * @brief Helper method of the export builtin for concatenation of env variables
 * with new values. Example: export PATH+=/home
 */
int	export_concat(char *str)
{
	t_env	*var;
	char	*concat_str;
	char	**slices;

	slices = ft_split(str, '+');
	if (!slices)
		return (perror("minishell (export_concat) - ft_split"), 1);
	if (slices[0][0] == '=')
		return (printf("export: Wrong syntax!\n"), free_array(slices), 1);
	var = env_get_key(slices[0]);
	concat_str = ft_calloc(export_concat_size(var, slices[1]), sizeof(char));
	if (!concat_str)
		return (perror("minishell (export_concat) - ft_calloc"),
			free_array(slices), 1);
	if (var && var->value)
	{
		ft_strlcpy(concat_str, var->value, ft_strlen(var->value) + 1);
		ft_strlcpy(concat_str + ft_strlen(var->value),
			slices[1] + 1, ft_strlen(slices[1]) + 1);
	}
	else
		ft_strlcpy(concat_str, slices[1] + 1, ft_strlen(slices[1]));
	if (env_set_key(slices[0], concat_str) == 1)
		return (free_array(slices), free(concat_str), 1);
	return (free_array(slices), free(concat_str), 0);
}

/**
 * @brief Sets a variable with a value of NULL or does nothing if the variable
 * already existed.
 * @param key The variable name to set to NULL.
 * @return The return value of env_set_key. 0 if the variable already existed.
 */
static int	export_no_value(char *key)
{
	t_env	*var;

	var = env_get_key(key);
	if (!var)
		return (env_set_key(key, NULL));
	return (0);
}

/**
 * @brief Extracts key and value from the command argv array and calls
 * env_set_key with them.
 *
 * @details The cmd argument should be an export command followed by a
 * key/value pair in the format key=value.
 *
 * @param str The key/value pair to extract from.
 * @param equal A pointer to the equal character in the key/value pair.
 * @return Return value of env_set_key. 1 if an error occurred.
 */
static int	export_value(char *str, char *equal)
{
	char	*key;
	char	*value;
	int		return_value;

	key = malloc(equal - str + 1);
	if (!key)
		return (perror("minishell (ft_export) - malloc"), 1);
	ft_strlcpy(key, str, equal - str + 1);
	value = ft_strdup(equal + 1);
	if (!value)
		return (perror("minishell (ft_export) - malloc"), free(key), 1);
	return_value = env_set_key(key, value);
	free(key);
	free(value);
	return (return_value);
}

/**
 * @return 0 if an already existing value was updated, 1 if a new value was
 * added, 1 if an error occurred.
 */
int	ft_export(t_command *cmd)
{
	int		i;
	char	*tmp;
	int		return_value;

	i = 1;
	if (!cmd->argv[i])
		return (export_print());
	while (cmd->argv[i])
	{
		if (check_name(cmd->argv[i]) == false)
			return (write(2, "minishell: export: `", 21),
				write(2, cmd->argv[i], ft_strlen(cmd->argv[i])),
				write(2, "' not a valid identifier\n", 26), 1);
		tmp = ft_strchr(cmd->argv[i], '=');
		if (!tmp)
			return_value = export_no_value(cmd->argv[i]);
		else if (tmp - ft_strchr(cmd->argv[i], '+') == 1)
			return_value = export_concat(cmd->argv[i]);
		else
			return_value = export_value(cmd->argv[i], tmp);
		if (return_value == 1)
			break ;
		i++;
	}
	return (return_value);
}
