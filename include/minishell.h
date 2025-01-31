/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by estettle          #+#    #+#             */
/*   Updated: 2025/01/31 11:19:02 by estettle         ###   ########.fr       */
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

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

// Builtins
int		ft_cd(t_token **token_list);
void	ft_exit(t_token **token_list);
int		ft_pwd(void);
int		ft_env(char **envp);

// Lexing
t_token	**init_token_list(char *input);

// Token tools
t_token	*token_new(char *token);
t_token	*token_last(t_token *list);
void	token_add_back(t_token **list, t_token *new);
void	token_add_front(t_token **list, t_token *new);
void	tokens_clear(t_token **list);

// Util functions
void	free_array(char **array);

// Command handler
void	command_handler(t_token **token_list, char **envp);

#endif //MINISHELL_H
