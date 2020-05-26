# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 11:27:08 by dheredat          #+#    #+#              #
#    Updated: 2020/05/26 09:48:11 by dheredat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIBFT_DIR =	./libft
SRC_DIR =	./src
INC_DIR =	./inc
OBJ_DIR =	./obj

FLAGS	=	-Wall -Wextra -Werror
HEAD	=	$(INC_DIR)/lem_in.h

SRC		=	algo_base.c\
			algo_coll.c\
			algo_core.c\
			algo_deep.c\
			coll_core.c\
			coll_fncs.c\
			coll_sort.c\
			free_fncs.c\
			main_core.c\
			map_build.c\
			map_check.c\
			map_get.c\
			map_reset.c\
			next_coll.c\
			next_norm.c\
			transport.c\
			way_build.c\
			way_copy.c\
			way_dstr.c\
			way_fncs.c

SRC_T	=	$(addprefix $(SRC_DIR)/,$(SRC))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT)
	gcc -g $(FLAGS) $(SRC_T) $(LIBFT) -o $(NAME)

clean:
	make -C libft clean

fclean:
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all