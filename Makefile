# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 16:43:02 by acourtar          #+#    #+#              #
#    Updated: 2023/04/05 12:46:06 by acourtar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
LIBFT		:=	libft/libft.a
CFLAGS		:=	-Wall -Werror -Wextra
NAME		:=	pipex
OBJFILES	:=	pipex.o \
			process_forking.o \
			struct_init.o \
			fd_init.o \
			path_creation.o
HEADERFILE	:=	pipex.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) -o $(NAME)

re: fclean all

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJFILES)

fclean:
	$(MAKE) fclean -C libft
	rm -f $(OBJFILES) $(NAME)

ft_%.o: ft_%.c $(HEADERFILE)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBFT):
	$(MAKE) -C libft

noclutter:
	$(MAKE)
	$(MAKE) clean

fsanitize: $(NAME)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) -fsanitize=address -o $(NAME)