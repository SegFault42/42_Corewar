# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcazako <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/19 18:05:50 by jcazako           #+#    #+#              #
#    Updated: 2017/02/19 18:08:02 by jcazako          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make all -C ./asm/
	make all -C ./vm/
clean:
	make clean -C ./asm/
	make clean -C ./vm/

fclean:
	make fclean -C ./asm/
	make fclean -C ./vm/

re:
	make re -C ./asm/
	make re -C ./vm/
