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
				$(SRCDIR)/lexing.c \
				$(SRCDIR)/command_handler.c \
				$(SRCDIR)/token_tools.c
OBJS		=	$(CFILES:.c=.o)

INCLDIR		=	include/
IFILES		=	$(INCLDIR)minishell.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

PRINTF_DIR	=	./ft_printf
PRINTF		=	$(PRINTF_DIR)/libftprintf.a

LIBS		=	-L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -lreadline

# Link GNU readline on my mac
UNAME_S		= 	$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
$(info MacOS detected, linking with custom GNU Readline...)
LIBS		+=	-L/opt/homebrew/opt/readline/lib -lreadline
endif

all:			$(NAME)

# Build libft first
$(LIBFT):
				@echo "Compiling libft"
				@$(MAKE) -C $(LIBFT_DIR)

# Build printf after libft
$(PRINTF):		$(LIBFT)
				@echo "Compiling ft_printf"
				@$(MAKE) -C $(PRINTF_DIR)

# Compile object files
%.o:			%.c $(IFILES)
ifeq ($(UNAME_S),Darwin) # Is on MacOS
				$(CC) $(CFLAGS) -I$(INCLDIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR)/include -I/opt/homebrew/opt/readline/include -c $< -o $@
else # Is on anything else
				$(CC) $(CFLAGS) -I$(INCLDIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR)/include -c $< -o $@

# Compile minishell with the existing libs
$(NAME):		$(OBJS) $(LIBFT) $(PRINTF)
				@echo "Compiling $(NAME)"
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
				@echo "$(NAME) created successfully"

clean:
				$(RM) $(RMFLAGS) $(OBJS)
				@cd $(LIBFT_DIR) && make clean
				@cd $(PRINTF_DIR) && make clean

fclean:			clean
				$(RM) $(RMFLAGS) $(NAME)
				@cd $(LIBFT_DIR) && make fclean
				@cd $(PRINTF_DIR) && make fclean

re:				fclean all

.PHONY:			all clean fclean re