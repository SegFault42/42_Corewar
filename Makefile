# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/02/18 11:57:42 by rabougue         ###   ########.fr        #
#    Updated: 2017/02/17 14:32:22 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@make all -C ./asm_work/asm_source/
	@make all -C ./vm/

clean:
	@make clean -C ./asm_work/asm_source/
	@make clean -C ./vm/

fclean:
	@make fclean -C ./asm_work/asm_source/
	@make fclean -C ./vm/

re: fclean all
