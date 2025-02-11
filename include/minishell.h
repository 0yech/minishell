/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by estettle          #+#    #+#             */
/*   Updated: 2025/02/11 10:50:51 by estettle         ###   ########.fr       */
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
# include "ft_printf.h"

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
}	t_token;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
	struct s_env *prev;
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
int		ft_env();

// Lexing
t_token	**init_token_list(char *input);

// Environ, environ.c
void	env_init(char **envp);
t_env	**get_env(void);

// Clear environ, env_clear.c
void	env_clear(t_env **envcpy);
void	env_delone(t_env *envcpy);

// Fill env name to list, env_set_name.c
int		fill_env_node(char *envp, t_env *node);

// Token tools
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
