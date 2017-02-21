# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/02/21 19:20:01 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################_COLOR_#####################################
GREEN = \033[38;5;10m
GREY = \033[38;5;60m
RED = \033[38;5;9m
END = \033[0m
##################################_COMPILATION_#################################
NAME = asm
CC = clang
FLAG = -Wall -Wextra -Werror
LFT = ./libft/libft.a
SRC = ./source
SRCS = $(SRC)/main.c \
	   $(SRC)/parse_s_file.c\
	   $(SRC)/parse_comment.c\
	   $(SRC)/parse_name.c\
	   $(SRC)/tools.c\
	   $(SRC)/parse_instructions.c\
	   $(SRC)/parse_info.c\
	   $(SRC)/t_info.c\
	   $(SRC)/ocp.c\
	   $(SRC)/check_param.c\
	   $(SRC)/clear_line.c\
	   $(SRC)/write_param.c\
	   $(SRC)/count_byte_inst.c\
	   $(SRC)/get_label_val.c\
	   $(SRC)/invert.c\
	   $(SRC)/write_nb_inst.c\
	   $(SRC)/error.c\
	   $(SRC)/free_glob.c\
	   $(SRC)/parse_instructions_1.c\
	   $(SRC)/write_param_1.c\
	   $(SRC)/check.c\
	   $(SRC)/check_1.c\

INCLUDE = -I ./include/ -I ./libft/includes/

OBJS = $(SRCS:.c=.o)

###########################_RELINK_MODIFY_.h####################################
RELINK_H = ./include/common.h
################################################################################

###################################Compilation##################################
all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C ./libft/
	@$(CC) -o $(NAME) $(LFT) $(OBJS)
	@printf "\n✅  Compilation done.\n"
	@cp ./asm ../

%.o : %.c $(RELINK_H) ./Makefile
	@printf "                                                               \r"
	@printf "✅  $(notdir $<)\r"
	@$(CC) -c $(FLAG) $< $(INCLUDE) -o $@

clean:
	@printf "                                                               \r"
	@printf "✅  all .o deleted\n"
	@rm -f $(OBJS)
	@make -s clean -C ./libft/

fclean:
	@printf "                                                               \r"
	@printf "✅  libft.a, all .o and rabougue.filler deleted\n"
	@rm -f $(NAME) $(CHECKER) $(OBJS) $(OBJS_CHECKER)
	@make -s fclean -C ./libft/
	@rm -fr *.cor

re: fclean all
