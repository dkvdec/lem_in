# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 15:36:22 by dheredat          #+#    #+#              #
#    Updated: 2019/10/26 17:33:29 by dheredat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
F = -Wall -Wextra

LIBFT = ./libft
SRC = ./src
INC = ./inc
OBJ = ./obj

SRCC = pf_char.c\
pf_colour.c\
pf_decimal_op.c\
pf_decimal.c\
pf_f_common.c\
pf_f_frc_op.c\
pf_f_frc_str.c\
pf_f_int_op.c\
pf_f_int_str.c\
pf_f_parser.c\
pf_f_pwr.c\
pf_f_round.c\
pf_float.c\
pf_l_double.c\
pf_uns_oct_hex_op.c\
pf_uns_oct_hex.c\
proto_common_func.c\
proto_common.c\
proto_core_get.c\
proto_core.c\
proto_flag_p2.c\
proto_flag.c\
proto_vlst_funcs_p2.c\
proto_vlst_funcs.c\
proto_vlst_p4.c\
proto_vlst_size_p2.c\
proto_vlst_size.c\
proto_vlst_type_p2.c\
proto_vlst_type.c\

OBJS = $(addprefix $(OBJ)/,$(SRCC:%.c=%.o))
LIBFT_LIB = $(LIBFT)/libft.a
LIBFT_H = $(LIBFT)


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(OBJS)
	@ar rcs $(NAME) $(OBJS) $(LIBFT)/*.o
	@ranlib $(NAME)
	@echo "\033[1;32mlibftprintf.a was built\033[0m"

$(OBJ):
	@mkdir -p $(OBJ)

$(LIBFT_LIB):
	@make -C libft

$(OBJ)/%.o: $(SRC)/%.c
	@gcc $F -c $< -I$(INC) -I$(LIBFT_H) -o $@

clean:
	@rm -Rf $(OBJ)
	@make -C libft clean
	@echo "\033[3;36mProject cleaned\033[0m"


fclean: clean
	@rm -Rf $(NAME)
	@make -C libft fclean
	@echo "\033[3;36mProject fully cleaned\033[0m"


re: fclean all

norm:
	norminette

test: $(LIBFT)
	@gcc -g -Wall -Wextra main.c $(NAME) $(LIBFT_LIB) -I./inc -I./libft -o test
