/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:37:16 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/16 15:44:05 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	error(uint8_t error)
{
	if (error == INIT_VIDEO_ERROR)
		ft_fprintf(2, RED"Failed to init SDL video.\n"END);
	else if (error == CREATE_WINDOW_ERROR)
		ft_fprintf(2, RED"Failed to create window.\n"END);
	exit(EXIT_FAILURE);
}

void	close_window(t_win *win, int8_t error)
{
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	SDL_Quit();
	if (error == ERROR)
		exit(EXIT_FAILURE);
}

void	change_text_color(SDL_Color text_color, uint8_t r, uint8_t g, uint8_t b)
{
	text_color.r = r;
	text_color.r = g;
	text_color.r = b;
	text_color.a = 255;
}

void	fill_octet(char *mem, uint8_t octet)
{
	char const *base = "0123456789ABCDEF";

	mem[0] = base[octet >> 4];
	mem[1] = base[octet % 16];
	mem[2] = '\0';
}
