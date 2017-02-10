/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/09 07:10:30 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	error(uint8_t error)
{
	if (error == INIT_VIDEO_ERROR)
		ft_printf("{:red}Failed to init SDL video.{:eoc}\n");
	else if (error == CREATE_WINDOW_ERROR)
		ft_printf("{:red}Failed to create window.{:eoc}\n");
	exit(EXIT_FAILURE);
}

void	sdl_clear(t_win *win, uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetRenderDrawColor(win->render, r, g, b, 255);
	SDL_RenderClear(win->render);
}

void	close_window(t_win *win, int8_t error)
{
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	SDL_Quit();
	if (error == ERROR)
		exit(EXIT_FAILURE);
}

void	sdl_draw_rectangle(t_win *win, int origin_x, int origin_y, int size_x, int size_y)
{
	int	x;
	int	y;

	y = -1;
	while (y++ < size_y)
	{
		x = -1;
		while (x++ < size_x)
			SDL_RenderDrawPoint(win->render, origin_x + x, origin_y + y);
		++y;
	}
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
		font->text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte sera place
	}
	font->text_rect.y = 1000; // coord y ou le texte sera place
	font->text_rect.x = 1000; // coord y ou le texte sera place
	font->text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte sera place
	font->text_rect.y = ORIGIN_TEXT_Y; // coord y ou le texte sera place
}

void	write_general_info(t_font *font_general, t_env *env, t_win *win)
{
	char	*str = NULL;

	font_general->text_rect.x = 1510; // coord y ou le texte sera place
	font_general->text_rect.y = 38; // coord y ou le texte sera place
	str = ft_itoa(env->cycle);
	draw_text(font_general, win, str, 0);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);

	font_general->text_rect.x = 1500; // coord y ou le texte sera place
	font_general->text_rect.y = 83; // coord y ou le texte sera place
	str = cycle_to_die(env);
	draw_text(font_general, win, str, 0);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);

	font_general->text_rect.x = 1410; // coord y ou le texte sera place
	font_general->text_rect.y = 129; // coord y ou le texte sera place
	str = write_lives(env);
	draw_text(font_general, win, str, 0);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);

	font_general->text_rect.x = 1520; // coord y ou le texte sera place
	font_general->text_rect.y = 175; // coord y ou le texte sera place
	str = process_alives(env);
	draw_text(font_general, win, str, 0);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
	
	font_general->text_rect.x = 1487; // coord y ou le texte sera place
	font_general->text_rect.y = 221; // coord y ou le texte sera place
	str = max_check(env);
	draw_text(font_general, win, str, 0);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
	
	font_general->text_rect.x = 1550; // coord y ou le texte sera place
	font_general->text_rect.y = 267; // coord y ou le texte sera place
	str = ft_itoa(env->last_live);
	draw_text(font_general, win, str, 0);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
}

void	write_challengers(t_font *font_general, t_win *win)
{
	t_env	*e;

	e = get_env();
	if (e->nb_player > 0)
	{
		font_general->text_rect.x = 1423; // coord y ou le texte sera place
		font_general->text_rect.y = 683; // coord y ou le texte sera place
		draw_text(font_general, win, e->player[0].header.prog_name, 0);
		SDL_DestroyTexture(font_general->texture);
	}
	if (e->nb_player > 1)
	{
		font_general->text_rect.x = 1423; // coord y ou le texte sera place
		font_general->text_rect.y = 757; // coord y ou le texte sera place
		draw_text(font_general, win, e->player[1].header.prog_name, 0);
		SDL_DestroyTexture(font_general->texture);
	}
	if (e->nb_player > 2)
	{
		font_general->text_rect.x = 1423; // coord y ou le texte sera place
		font_general->text_rect.y = 832; // coord y ou le texte sera place
		draw_text(font_general, win, e->player[2].header.prog_name, 0);
		SDL_DestroyTexture(font_general->texture);
	}
	if (e->nb_player > 3)
	{
		font_general->text_rect.x = 1423; // coord y ou le texte sera place
		font_general->text_rect.y = 902; // coord y ou le texte sera place
		draw_text(font_general, win, e->player[3].header.prog_name, 0);
		SDL_DestroyTexture(font_general->texture);
	}
}

void	general_info(t_font *font_general, t_win *win)
{
	font_general[1].font_size = 25;
	select_font(win, &font_general[1], "/Library/Fonts/Arial Bold.ttf");
	font_general[1].text_color = (SDL_Color){174, 174, 174, 255};

	font_general[2].font_size = 50;
	select_font(win, &font_general[2], "./font/ufonts.com_american-typewriter-bold.ttf");
	font_general[2].text_color = (SDL_Color){174, 174, 174, 255};
}

int		gui(t_env *env, t_sdl *sdl)
{
	SDL_RenderCopy((sdl->win).render, (sdl->wallpaper).texture, NULL, NULL);
	draw_memory(&(sdl->win), &(sdl->font[0]));
	write_general_info(&(sdl->font[1]), env, &(sdl->win));
	write_challengers(&(sdl->font[2]), &(sdl->win));
	if (SDL_PollEvent(&(sdl->event)))
	{
		if ((sdl->event).type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
			return (0);
		if (button_press(&(sdl->event), &(sdl->wallpaper), &(sdl->win)) == true)
			return (0);
	}
	SDL_RenderPresent((sdl->win).render);
	return (1);
}
