# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 11:27:08 by dheredat          #+#    #+#              #
#    Updated: 2020/05/09 14:10:03 by dheredat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

LIBFT_DIR =	./libft
SRC_DIR =	./src
INC_DIR =	./inc
OBJ_DIR =	./obj

FLAGS	=	-Wall -Wextra -Werror
HEAD	=	$(INC_DIR)/lem_in.h

SRC		=	base_algo.c base_way.c build_map.c\
			check_map.c get_map.c test.c\
			new_transport.c new_way.c\
			way_copy.c way_dstr.c way_coll.c\
			test_show.c new_algo.c

SRC_T	=	$(addprefix $(SRC_DIR)/,$(SRC))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT)
	gcc -g $(SRC_T) $(LIBFT) -o $(NAME)

clean:
	make -C libft clean

fclean:
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all