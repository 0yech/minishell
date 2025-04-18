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

// TODO : can't set a variable containing ? in its name AND
// printing echo $?hello should print <exitstatus>hello
// TODO : Hide _ and ? variables from export output

/**
 * @brief Prints all exported variables to stdout formatted as
 * export <key>="<value>".
 * 
 * @return 0 if all went well, -1 if an error occurred.
 */
int	export_print(void)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	env = *env_get();
	if (!env)
		return (-1);
	tmp = NULL;
	i = env_size(env);
	while (i--)
	{
		tmp = find_lowest_str(env, tmp);
		if (tmp->name && (write(STDOUT_FILENO, "export ", 7) == -1
				|| write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name)) == -1))
			return (perror("minishell (export_print) - write"), 0);
		if (tmp->value && tmp->value[0] && (write(STDOUT_FILENO, "=\"", 2) == -1
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

static int	export_no_value(char *str)
{
	t_env	*var;

	var = env_get_key(str);
	if (!var)
		return (env_set_key(str, NULL));
	return (0);
}

static int	export_value(t_command *cmd, char *tmp, int i)
{
	char	*key;
	char	*value;
	int		return_value;

	key = malloc(tmp - cmd->argv[i] + 1);
	if (!key)
		return (perror("minishell (ft_export) - malloc"), 1);
	ft_strlcpy(key, cmd->argv[i], tmp - cmd->argv[i] + 1);
	value = ft_strdup(tmp + 1);
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
		if (ft_isdigit(*cmd->argv[i]) || *cmd->argv[i] == '=')
			return (write(2, "minishell: export: `", 21),
				write(2, cmd->argv[i], ft_strlen(cmd->argv[i])),
				write(2, "' not a valid identifier\n", 26), 1);
		tmp = ft_strchr(cmd->argv[i], '=');
		if (!tmp)
			return_value = export_no_value(cmd->argv[i]);
		else if (tmp - ft_strchr(cmd->argv[i], '+') == 1)
			return_value = export_concat(cmd->argv[i]);
		else
			return_value = export_value(cmd, tmp, i);
		if (return_value == 1)
			break ;
		i++;
	}
	return (return_value);
}
