# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 16:05:27 by qhonore           #+#    #+#              #
#    Updated: 2017/02/09 06:04:50 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/ ./libft/include/
LIB_PATH = ./libft/

SRC_NAME = main.c dump_memory.c globals.c init.c init2.c ocp.c\
		   get_memory.c set_memory.c utils.c utils2.c instructions.c\
		   instructions2.c instructions3.c instructions4.c\
		   ft_load.c run.c exit.c utils3.c instructions5.c\
		   gui.c font.c tools.c init_sdl.c draw_text.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = -lft
NAME = corewar
DEP = include/vm.h

####################################FOR_SDL#####################################
LSDL = -L ./libsdl/ -lSDL2
FRAMEWORK = -framework OpenGL
SDL2DYLIB = ./libsdl/libSDL2-2.0.0.dylib
#SDL2_image = ./libsdl/SDL2_image # ok sur elcapitan
SDL2_image = ./libsdl/SDL2_image.framework/Versions/A/SDL2_image
SDL2_ttf = ./libsdl/SDL2_ttf.framework/Versions/A/SDL2_ttf
SDL2_mixer = ./libsdl/SDL2_mixer.framework/Versions/A/SDL2_mixer
SDL2_smpeg2 = ./libsdl/SDL2_mixer.framework/Versions/A/Frameworks/smpeg2.framework/smpeg2
################################################################################

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L,$(LIB_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: lib
	@echo "\033[32;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(LIB_NAME) $(LSDL) $(LIB) $(SDL2_ttf) $(SDL2_mixer) $(SDL2_image) $(INC) $^ -o $@ $(FRAMEWORK)
	@install_name_tool -change /usr/local/lib/libSDL2-2.0.0.dylib $(SDL2DYLIB) $(NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_mixer) $(NAME)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2DYLIB) $(SDL2_ttf)
	@install_name_tool -change @executable_path/../Frameworks/SDL2.framework/Versions/A/SDL2 $(SDL2DYLIB) $(SDL2_smpeg2)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

lib:
	@make -C ./libft/

clean:
	rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all

.PHONY: lib clean fclean re
