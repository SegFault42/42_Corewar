/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/16 15:49:16 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_memory(t_win *win, t_font *font)
{
	int8_t	x;
	int8_t	y;
	int		i;
	char	memory[3];

	y = -1;
	i = 0;
	while (y++ < 63)
	{
		x = -1;
		while (x++ < 63)
		{
			fill_octet(memory, g_mem[i]);
			draw_text(font, win, memory, i);
			SDL_DestroyTexture(font->texture);
			font->text_rect.x += INCR_TEXT_X;
			++i;
		}
		font->text_rect.y += INCR_TEXT_Y;
		font->text_rect.x = ORIGIN_TEXT_X;
	}
	font->text_rect.y = 1000;
	font->text_rect.x = 1000;
	font->text_rect.x = ORIGIN_TEXT_X;
	font->text_rect.y = ORIGIN_TEXT_Y;
}

void	write_challengers(t_font *font_general, t_win *win)
{
	t_env	*e;

	e = get_env();
	font_general->text_rect.x = 1423;
	if (e->nb_player > 0)
	{
		font_general->text_rect.y = 683;
		draw_text(font_general, win, e->player[0].header.prog_name, GREEN_TEXT);
	}
	if (e->nb_player > 1)
	{
		font_general->text_rect.y = 757;
		draw_text(font_general, win, e->player[1].header.prog_name, P_TEXT);
	}
	if (e->nb_player > 2)
	{
		font_general->text_rect.y = 832;
		draw_text(font_general, win, e->player[2].header.prog_name, CYAN_TEXT);
	}
	if (e->nb_player > 3)
	{
		font_general->text_rect.y = 902;
		draw_text(font_general, win, e->player[3].header.prog_name, Y_TEXT);
	}
}

void	general_info(t_font *font_general, t_win *win)
{
	font_general[1].font_size = 25;
	select_font(win, &font_general[1], "/Library/Fonts/Arial Bold.ttf");
	font_general[1].text_color = (SDL_Color){174, 174, 174, 255};
	font_general[2].font_size = 50;
	select_font(win, &font_general[2],
			"./font/ufonts.com_american-typewriter-bold.ttf");
	font_general[2].text_color = (SDL_Color){174, 174, 174, 255};
}

void	gui(t_env *env, t_sdl *sdl)
{
	SDL_RenderCopy((sdl->win).render, (sdl->wallpaper).texture, NULL, NULL);
	draw_memory(&(sdl->win), &(sdl->font[0]));
	write_general_info(&(sdl->font[1]), env, &(sdl->win));
	write_challengers(&(sdl->font[2]), &(sdl->win));
	if (SDL_PollEvent(&(sdl->event)))
	{
		if ((sdl->event).type == SDL_QUIT)
			env->run = 0;
		if (button_press(&(sdl->event), &(sdl->win), sdl) == true)
			env->run = 0;
	}
	SDL_RenderPresent((sdl->win).render);
}
