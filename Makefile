# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 11:27:08 by dheredat          #+#    #+#              #
#    Updated: 2020/04/12 13:39:20 by dheredat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

LIBFT_DIR =	./ft_printf
SRC_DIR =	./src
INC_DIR =	./inc
OBJ_DIR =	./obj

FLAGS	=	-Wall -Wextra -Werror
HEAD	=	$(INC_DIR)/lem_in.h

SRC		=	valid.c parser.c transport.c\
			algo_proto.c make_way_proto.c

SRC_T	=	$(addprefix $(SRC_DIR)/,$(SRC))

LIBFT = $(LIBFT_DIR)/libftprintf.a

all: $(NAME)

$(LIBFT):
	make -C ft_printf

$(NAME):
	gcc -g $(SRC_T) $(LIBFT) -o $(NAME)

clean:
	make -C ft_printf clean

fclean:
	rm -rf $(NAME)
	make -C ft_printf fclean

re: fclean all