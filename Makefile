NAME		=		minishell
CC			=		cc
CFLAGS		=		-Wall -Wextra -Werror
RM			=		rm
RMFLAGS		=		-f
SRCDIR		=		src/
CFILES		=		$(SRCDIR)minishell.c
OBJS		=		$(CFILES:.c=.o)
INCLDIR		=		include/
IFILES		=		$(INCLDIR)minishell.h
LIBFTDIR	=		libft/
LIBFT		=		$(LIBFTDIR)libftprintf.a

all:				$(NAME)


$(NAME):			$(OBJS) $(LIBFT)


%.o:				%.c
					$(CC) $(CFLAGS) -I$(INCLDIR) $^ -o $@

$(LIBFT):
					make -C $(LIBFTDIR)

clean:
					$(RM) $(RMFLAGS) $(OBJS)
					cd $(LIBFTDIR) && make clean
fclean:				clean
					$(RM) $(RMFLAGS) $(NAME)
					cd $(LIBFTDIR) && make fclean
re:					fclean all


.PHONY:				all clean fclean re