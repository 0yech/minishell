/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by estettle          #+#    #+#             */
/*   Updated: 2025/03/26 13:48:42 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdbool.h>

// Libft
# include "libft.h"

// Enums
typedef enum e_token_type
{
	X,
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	DELIM,
	REDIRECT_FILE,
	APPEND,
	OPTION,
}	t_token_type;

typedef enum e_outtype
{
	Z,
	RED_OUT,
	APD,
}	t_outtype;

// Structs
typedef struct s_fd
{
	char		*input;
	char		*output;
	t_outtype	outtype;
	int			fdin;
	int			fdout;
	int			stdincpy;
	int			stdoutcpy;
}	t_fd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_command
{
	char				*command;
	t_fd				*fdio;
	t_token				**arguments; // Array of all tokens associated with cmd
	char				**argv; // Array of argv tokens
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// Display prompt + Git - git_handler.c
void		display_prompt(void);

// Builtins - builtins folder
int			ft_cd(t_command *cmd);
void		ft_exit(t_command *cmd);
int			ft_pwd(void);
int			ft_env(void);
int			ft_export(char *str);
int			ft_echo(t_command *cmd);
int			ft_unset(char *key);

// Lexing - Main, lexing.c
t_token		**init_token_list(char *input);
void		assign_types(t_token **token_list);

// Lexing - Quotes, lexing_quotes.c
int			quotes_handler(char *str);
char		*quotes_clean(char *raw_token);

// Lexing - Var expansion, lexing_expand_var.c
char		*var_expand(char *token);

// Environ, environ.c
void		env_init(char **envp);
t_env		**env_get(void);

// Env list utils, env_list.c
void		env_clear(t_env **envcpy);
void		env_delone(t_env *envcpy);
t_env		*env_last(void);
t_env		*env_new(char *key, char *value, t_env *prev, t_env *next);

// Fill env name to list, env_set_list.c
int			env_fill_node(char *envp, t_env *node);
int			env_set_key(char *key, char *value);

// Env utils, env_utils.c
char		**env_to_char(t_env *env);
t_env		*env_get_key(char *key);
int			env_size(t_env *env);

// Token tools
void		print_tokens(t_token *list); // This one's temporary
t_token		*token_new(char *token);
t_token		*token_last(t_token *list);
void		token_add_back(t_token **list, t_token *new);
void		token_add_front(t_token **list, t_token *new);
void		tokens_clear(t_token **list);

// Util functions
void		free_array(char **array);

// Command handler
void		command_handler(t_token **token_list);

void		signal_handler(void);

t_command	*parsing_handler(t_token **token_list);
int			no_cmd_checks(t_token *token_list);
void		free_command_list(t_command *cmd);
int			exec_checks(t_command *current);

// Heredoc handler - heredoc_handler.c
void		heredoc_handler(t_command *cmd, char *hd_delim);
void		process_heredoc(t_command *cmd);

int			valid_pipes(t_token *token);
void		assign_pipes(t_command *cmd_list);
int			execute_piped_commands(t_command *cmd);
int			exec_update_env(t_command *cmd, int exit_status);
char		*find_executable_path(char *command);
int			is_builtin(t_command *current);

// Parsing arguments - parsing_args.c
t_token		**extract_args(t_token *token);
char		**args_to_argv(t_token *arg);

#endif //MINISHELL_H
