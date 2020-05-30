# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 13:31:57 by dheredat          #+#    #+#              #
#    Updated: 2020/05/30 19:58:01 by dheredat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR =	./src
INC_DIR =	./inc
OBJ_DIR =	./obj

FLAGS	=	-Wall -Wextra -Werror
HEAD	=	$(INC_DIR)/libft.h

SRC =	ft_isprint.c ft_lstnew.c ft_memmove.c ft_putnbr_fd.c ft_strcpy.c \
		ft_strlcat.c ft_strnequ.c ft_strsub.c ft_atoi.c ft_itoa.c \
		ft_memalloc.c ft_memset.c ft_putstr.c ft_strdel.c ft_strlen.c \
		ft_strnew.c ft_strtrim.c ft_bzero.c ft_lstadd.c ft_memccpy.c \
		ft_putchar.c ft_putstr_fd.c ft_strdup.c ft_strmap.c ft_strnlen.c \
		ft_tolower.c ft_isalnum.c ft_lstdel.c ft_memchr.c ft_putchar_fd.c \
		ft_strcat.c ft_strequ.c ft_strmapi.c ft_strnstr.c ft_toupper.c \
		ft_isalpha.c ft_lstdelone.c ft_memcmp.c ft_putendl.c ft_strchr.c \
		ft_striter.c ft_strncat.c ft_strrchr.c ft_isascii.c ft_lstiter.c \
		ft_memcpy.c ft_putendl_fd.c ft_strclr.c ft_striteri.c ft_strncmp.c \
		ft_strsplit.c ft_isdigit.c ft_lstmap.c ft_memdel.c ft_putnbr.c \
		ft_strcmp.c ft_strjoin.c ft_strncpy.c ft_strstr.c ft_bzero_safe.c

SRCS	=	$(addprefix $(SRC_DIR)/,$(SRC))
OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "\033[35mBuilding libft.a\033[0m"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[1;32mDone libft.a\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	@gcc $(FLAGS) -g -c $< -I$(INC_DIR) -o$@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
