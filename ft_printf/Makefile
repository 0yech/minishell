# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/15 14:23:38 by nrey              #+#    #+#              #
#    Updated: 2024/11/01 16:32:19 by cheyo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a
CC=cc
INCLUDE=include
LIBFTDIR=../libft
SRCDIR=src
CFLAGS=-Wall -Werror -Wextra -g
AR=ar
ARFLAGS=rcs
RM=rm -f
CFILES=$(SRCDIR)/ft_printf.c \
	   $(SRCDIR)/ft_printf_put.c \
	   $(SRCDIR)/ft_printf_xp.c

OFILES=$(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES) $(LIBFTDIR)/libft.a
	@echo "Making $(NAME) with libft from rootdir"
	@cp $(LIBFTDIR)/libft.a $(NAME)
	@$(AR) $(ARFLAGS) $(NAME) $(OFILES)
	@echo "$(NAME) Created successfully"

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFTDIR) -c $< -o $@

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
