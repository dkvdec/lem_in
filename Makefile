# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 11:27:08 by dheredat          #+#    #+#              #
#    Updated: 2020/05/30 18:39:42 by dheredat         ###   ########.fr        #
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

SRCS	=	$(addprefix $(SRC_DIR)/,$(SRC))
OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@echo "\033[35mBuilding lem-in\033[0m"
	@gcc -g $(LIBFT) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "\033[1;32mDone lem-in\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	@gcc $(FLAGS) -g -c $< -I$(INC_DIR) -I$(LIBFT_DIR)/inc -o $@
	
clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all