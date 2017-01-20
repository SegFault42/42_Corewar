# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/01/20 21:32:40 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################_COLOR_#####################################
GREEN = \033[38;5;10m
GREY = \033[38;5;60m
RED = \033[38;5;9m
END = \033[0m
##################################_COMPILATION_#################################
NAME = gui
CC = clang
FLAG = -Wall -Wextra -Werror
LFT = ./libft/libft.a
SRC = ./source
SRCS = $(SRC)/main.c \
		$(SRC)/gui.c \

INCLUDE = -I ./include/ -I ./libft/includes/ -I ./libsdl/include/
#####################################_SDL_######################################
LSDL = -L ./libsdl/lib/ -lSDL2
#FRAMEWORK = -framework OpenGL

OBJS = $(SRCS:.c=.o)

###########################_RELINK_MODIFY_.h####################################
RELINK_H = ./include/common.h
################################################################################

###################################Compilation##################################
all: $(NAME)

install:
	@mkdir -p libsdl && cd libsdl && ../SDL2-2.0.5/configure --prefix=`pwd` && make && make install

$(NAME): $(OBJS)
	@make -s -C ./libft/
	@$(CC) $(LSDL) -o $(NAME) $(LFT) $(OBJS) $(FRAMEWORK)
	@printf "\n✅  Compilation done.\n"

%.o : %.c $(RELINK_H) ./Makefile
	@$(CC) -c $(FLAG) $< $(INCLUDE) -o $@

clean:
	@printf "                                                               \r"
	@printf "✅  all .o deleted\n"
	@rm -f $(OBJS)
	@make -s clean -C ./libft/

fclean:
	@printf "                                                               \r"
	@printf "✅  libft.a, all .o\n"
	@rm -f $(NAME) $(CHECKER) $(OBJS) $(OBJS_CHECKER)
	@make -s fclean -C ./libft/
	@rm -fr *.cor

re: fclean all
