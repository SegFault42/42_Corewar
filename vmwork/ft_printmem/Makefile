# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/17 15:39:34 by lfabbro           #+#    #+#              #
#    Updated: 2016/12/16 18:35:02 by lfabbro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printmem

SRC_NAME = main.c ft_printmem.c

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAME = -lft

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
LIB_PATH = ./libft/
INC_PATH = ./includes ./libft/includes ./libft/libft

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L, $(LIB_PATH))
INC = $(addprefix -I ,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: lib
	@echo "\033[32;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME) $(LIB) $(LIB_NAME)

.PHONY: all lib clean fclean re libfclean libclean

lib:
	@make -C ./libft

clean:
	@echo "\033[31;44m Removing $(NAME) objects \033[0m"
	@rm -rfv $(OBJ) $(OBJ_PATH)

fclean: clean
	@echo "\033[31;44m Removing $(NAME) executables \033[0m"
	@rm -fv $(NAME)

libclean:
	@echo "\033[31;44m Removing $(LIB_PATH) objects \033[0m"
	@make -C ./libft clean

libfclean:
	@echo "\033[31;44m Removing $(LIB_PATH) executables \033[0m"
	@make -C ./libft fclean

re: fclean
	@make all
