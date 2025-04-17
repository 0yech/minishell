/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by fireinside        #+#    #+#             */
/*   Updated: 2025/03/26 13:48:42 by fireinside       ###   ########.fr       */
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

# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define LIME	"\033[38;2;160;240;130m"
# define ORG	"\033[38;2;255;190;100m"
# define UNDER	"\033[4m"
# define BOLD	"\033[1m"
# define CYAN	"\033[36m"
# define RESET	"\033[0m"

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
typedef struct s_io
{
	int			fdin;
	int			fdout;
	int			stdincpy;
	int			stdoutcpy;
}	t_io;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	bool			quoted;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_command
{
	char				*command;
	t_io				*fdio;
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

// Prompt - prompt.c
void		display_prompt(void);

// Git prompt - prompt_git.c
char		*get_git_branch(void);

// Builtins - builtins folder
int			ft_cd(t_command *cmd);
void		ft_exit(t_command *cmd);
int			ft_pwd(void);
int			ft_env(void);
int			ft_export(t_command *cmd);
int			ft_echo(t_command *cmd);
int			ft_unset(char *key);

// Export builtin helper functions - export_utils.c
t_env		*find_lowest_str(t_env *lst, t_env *min);
size_t		export_concat_size(t_env *var, char *new_value);

// Lexing Main - lexing.c
t_token		**init_token_list(char *input);
void		assign_types(t_token **token_list);

// Lexing Quotes - lexing_quotes.c
int			quotes_handler(char *str);
char		*quotes_clean(t_token *token, char *raw_token);

// Lexing Var expansion - lexing_expand_var.c
char		*get_variable(char *str);
size_t		full_token_size(char *token);
void		handle_var(char *token, char *expanded_token, size_t *i, size_t *j);
char		*var_expand(char *token);

// Environ - environ.c
void		env_init(char **envp);
t_env		**env_get(void);

// Env list utils - env_list.c
void		env_clear(t_env **envcpy);
void		env_delone(t_env *envcpy);
t_env		*env_last(void);
t_env		*env_new(char *key, char *value, t_env *prev, t_env *next);

// Fill env name to list - env_set_list.c
int			env_fill_node(char *envp, t_env *node);
int			env_set_key(char *key, char *value);

// Env utils - env_utils.c
void		free_array(char **array);
char		**env_to_char(t_env *env);
t_env		*env_get_key(char *key);
int			env_size(t_env *env);

// Token tools - token_tools.c
t_token		*token_new(char *token);
t_token		*token_last(t_token *list);
void		token_add_back(t_token **list, t_token *new);
void		token_add_front(t_token **list, t_token *new);
void		tokens_clear(t_token **list);

// Command handler - command_handler.c
void		command_handler(t_token **token_list);

// Signal handler - signal_handler.c
void		ignore_sig(int signal_id);
void		signal_handler(void);

// Parsing - parsing.c
t_command	*parsing_handler(t_token **token_list);
int			exec_checks(t_command *current);

// Free parsing - free_parser.c
void		free_command_list(t_command *cmd);
void		command_delone(t_command *node);

// Parsing arguments - parsing_args.c
t_token		**extract_args(t_token *token);
char		**args_to_argv(t_token **arg);

// Heredoc handler - heredoc_handler.c
void		heredoc_handler(t_command *cmd, t_token *hd_delim);
void		process_heredoc(t_command *cmd);

// Invalid checks - invalid_checks.c
int			valid_pipes(t_token *token);

// Pipe assignation - pipe_assign.c
void		assign_pipes(t_command *cmd_list);

// Exec Tools - exec_tools.c
char		*find_executable_path(char *command);

// Exec Main - exec_pipes.c
int			execute_piped_commands(t_command *cmd);
int			exec_update_env(int exit_status);

// Exec fd/io - exec_io.c
int close_child(t_command* current);
int close_parent(t_command* current);
int			setup_redirections(t_command *cmd, t_token **arg);

// Exec builtins - exec_builtin.c
int			is_builtin(t_command *current);
int			exec_pipe_builtin(t_command *current);

// Help - help.c
void		help_menu(int argc, char **argv);
void		print_help_header(void);
void		print_void_lines(int amount);
void		help_echo(void);
void		help_cd(void);
void		help_export(void);
void		help_env(void);
void		help_exit(void);
void		help_unset(void);
void		help_pwd(void);

#endif //MINISHELL_H
