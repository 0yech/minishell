NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm
RMFLAGS		=	-f

SRCDIR		=	./src
CFILES		=	$(SRCDIR)/minishell.c \
				$(SRCDIR)/builtins/cd.c \
				$(SRCDIR)/builtins/exit.c \
				$(SRCDIR)/builtins/pwd.c \
				$(SRCDIR)/builtins/env.c \
				$(SRCDIR)/builtins/export.c \
				$(SRCDIR)/builtins/unset.c \
				$(SRCDIR)/builtins/echo.c \
				$(SRCDIR)/environ/environ.c \
				$(SRCDIR)/environ/env_list.c \
				$(SRCDIR)/environ/env_set_list.c \
				$(SRCDIR)/environ/env_utils.c \
				$(SRCDIR)/lexing/lexing.c \
				$(SRCDIR)/lexing/lexing_quotes.c \
				$(SRCDIR)/lexing/lexing_assign_type.c \
				$(SRCDIR)/lexing/lexing_expand_var.c \
				$(SRCDIR)/command_handler.c \
				$(SRCDIR)/signal/signal.c \
				$(SRCDIR)/parsing/parsing.c \
				$(SRCDIR)/parsing/free_parser.c \
				$(SRCDIR)/parsing/heredoc_handler.c \
				$(SRCDIR)/parsing/invalid_checks.c \
				$(SRCDIR)/parsing/pipe_assign.c \
				$(SRCDIR)/parsing/parsing_args.c \
				$(SRCDIR)/parsing/rights_checks.c \
				$(SRCDIR)/parsing/no_cmd_checks.c \
				$(SRCDIR)/exec/exec_pipes.c \
				$(SRCDIR)/exec/exec_tools.c \
				$(SRCDIR)/gitprompt/git_handler.c \
				$(SRCDIR)/token_tools.c
OBJS		=	$(CFILES:.c=.o)

INCLDIR		=	include/
IFILES		=	$(INCLDIR)minishell.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

LIBS		=	-L$(LIBFT_DIR) -lft -lreadline

# Link GNU readline on my mac
UNAME_S		= 	$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
$(info MacOS detected, linking with custom GNU Readline...)
LIBS		+=	-L/opt/homebrew/opt/readline/lib
endif

all:			$(NAME)

# Build libft first
$(LIBFT):
				@printf "\rCompiling libft"
				@make -C $(LIBFT_DIR) --no-print-directory
				@printf "\rCompiled libft successfully.\n"

# Compile object files
%.o:			%.c $(IFILES)
ifeq ($(UNAME_S),Darwin) # Is on MacOS
				@printf "\rCompiling $<..."
				@$(CC) $(CFLAGS) -I$(INCLDIR) -I$(LIBFT_DIR) -I/opt/homebrew/opt/readline/include -c $< -o $@
else # Is on anything else
				@printf "\rCompiling $<..."
				@$(CC) $(CFLAGS) -I$(INCLDIR) -I$(LIBFT_DIR) -c $< -o $@
endif

# Compile minishell with the existing libs
$(NAME):		$(OBJS) $(LIBFT)
				@printf "\rCompiling $(NAME)..."
				@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
				@printf "\r\n\033[32m$(NAME) compiled.\033[0m\n"
clean:
				@printf "\rCleaning object files"
				@$(RM) $(RMFLAGS) $(OBJS)
				@make clean -C $(LIBFT_DIR)/ --no-print-directory
				@printf "\rObject files cleaned.\n"

fclean:			clean
				@printf "\rRemoving $(NAME)..."
				@$(RM) $(RMFLAGS) $(NAME)
				@make fclean -C $(LIBFT_DIR)/ --no-print-directory
				@printf "\r$(NAME) Removed.\n"

re:				fclean all

.PHONY:			all clean fclean re