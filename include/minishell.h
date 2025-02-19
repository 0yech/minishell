/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by estettle          #+#    #+#             */
/*   Updated: 2025/02/19 11:00:54 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

// Libft
# include "libft.h"

// Enums
typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	END
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

// Builtins
int		ft_cd(t_token **token_list);
void	ft_exit(t_token **token_list);
int		ft_pwd(void);
int		ft_env(void);
int		ft_export(char *str);
int		ft_unset(char *key);

// Lexing
t_token	**init_token_list(char *input);

// Environ, environ.c
void	env_init(char **envp);
t_env	**env_get(void);

// Env list utils, env_list.c
void	env_clear(t_env **envcpy);
void	env_delone(t_env *envcpy);
t_env	*env_last(void);
t_env	*env_new(char *key, char *value, t_env *prev, t_env *next);

// Fill env name to list, env_set_list.c
int		env_fill_node(char *envp, t_env *node);
int		env_set(char *key, char *value);

// Env utils, env_utils.c
t_env	*get_key(char *key);

// Token tools
void	print_tokens(t_token *list); // This one's temporary
t_token	*token_new(char *token);
t_token	*token_last(t_token *list);
void	token_add_back(t_token **list, t_token *new);
void	token_add_front(t_token **list, t_token *new);
void	tokens_clear(t_token **list);

// Util functions
void	free_array(char **array);

// Command handler
void	command_handler(t_token **token_list);

#endif //MINISHELL_H
