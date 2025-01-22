/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by estettle          #+#    #+#             */
/*   Updated: 2025/01/22 15:33:02 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

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
	t_token_type	*type;
	struct s_token	*next;
}	t_token;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

// Builtins
int		ft_cd(char *path);

// Lexing
t_token	**init_token_list(char *input);

// Token tools
t_token *token_new(char *token);
t_token *token_last(t_token *list);
void	token_add_back(t_token **list, t_token *new);
void	token_add_front(t_token **list, t_token *new);
void	tokens_clear(t_token **list);

// Util functions
void	free_array(char **array);

#endif //MINISHELL_H
