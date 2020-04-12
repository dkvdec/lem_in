# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 11:27:08 by dheredat          #+#    #+#              #
#    Updated: 2020/04/12 12:21:29 by dheredat         ###   ########.fr        #
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

all: $(NAME)

$(NAME):
	gcc -g $(SRC_T) $(SRC_DIR)/libftprintf.a -o $(NAME)