/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/02 17:25:55 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	error(uint8_t error)
{
	if (error == INIT_VIDEO_ERROR)
		ft_fprintf(2, RED"Failed to init SDL video.\n"END);
	else if (error == CREATE_WINDOW_ERROR)
		ft_fprintf(2, RED"Failed to create window.\n"END);
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

void	draw_memory(t_win *win, t_font *font)
{
	int8_t	x;
	int8_t	y;
	int		i;
	char	frag_memory[MEM_SIZE / MEM_SIZE];
	char	*memory;

	y = -1;
	i = 0;
	memory = NULL;
	while (y++ < 63)
	{
		x = -1;
		while (x++ < 63)
		{
			ft_memmove(frag_memory, &g_memory[i], 1);
			memory = ft_hexa_itoa(frag_memory[i], 1);
			draw_text(font, win, memory, i);
			free(memory);
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

void	fill_memory()
{
	int i = -1;

	while (i++ < MEM_SIZE)
		g_memory[i] = 'A' + random() % 26;
	i = -1;
	while (i++ < 50)
	{
		g_memory_color[i + random() % MEM_SIZE] = 1;
		g_memory_color[i + random() % MEM_SIZE] = 2;
		g_memory_color[i + random() % MEM_SIZE] = 3;
		g_memory_color[i +random() % MEM_SIZE] = 4;
	}
}

static void init_env(t_env *env)
{
	env->nb_player = 2;
	env->nb_process = random() % 50;
	env->cur_process = random() % 50;
	env->cur_die = random() % 50;
	env->cycle_die = random() % 50;
	env->check = random() % 50;
	env->lives = 22;
	env->alives = 4;
	env->cycle -= 1;
}

void	write_general_info(t_font *font_general, t_env *env, t_win *win)
{
	char	*itoa;

	font_general->text_rect.x = 1420; // coord y ou le texte sera place
	font_general->text_rect.y = 38; // coord y ou le texte sera place
	itoa = ft_itoa(env->cycle);
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);

	itoa = ft_itoa(env->nb_process);
	font_general->text_rect.x = 1680; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);
	
	itoa = ft_itoa(env->lives);
	font_general->text_rect.x = 1850; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);
	
	itoa = ft_itoa(env->cur_die);
	font_general->text_rect.x = 1500; // coord y ou le texte sera place
	font_general->text_rect.y = 87; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);
	
	itoa = ft_itoa(env->cur_die);
	font_general->text_rect.x = 1720; // coord y ou le texte sera place
	font_general->text_rect.y = 87; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);
	
	itoa = ft_itoa(env->check);
	font_general->text_rect.x = 1510; // coord y ou le texte sera place
	font_general->text_rect.y = 137; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);
	
	itoa = ft_itoa(env->alives);
	font_general->text_rect.x = 1760; // coord y ou le texte sera place
	font_general->text_rect.y = 137; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);

	itoa = ft_itoa(win->delay / 10 * -1);
	font_general->text_rect.x = 1540; // coord y ou le texte sera place
	font_general->text_rect.y = 1015; // coord y ou le texte sera place
	draw_text(font_general, win, itoa, 0);
	ft_strdel(&itoa);
	SDL_DestroyTexture(font_general->texture);
}

void	write_challengers(t_font *font_general, t_win *win)
{
	font_general->text_rect.x = 1423; // coord y ou le texte sera place
	font_general->text_rect.y = 683; // coord y ou le texte sera place
	draw_text(font_general, win, "Helltain", 0);
	SDL_DestroyTexture(font_general->texture);
	
	font_general->text_rect.x = 1423; // coord y ou le texte sera place
	font_general->text_rect.y = 757; // coord y ou le texte sera place
	draw_text(font_general, win, "Zork", 0);
	SDL_DestroyTexture(font_general->texture);

	font_general->text_rect.x = 1423; // coord y ou le texte sera place
	font_general->text_rect.y = 832; // coord y ou le texte sera place
	draw_text(font_general, win, "BigZork", 0);
	SDL_DestroyTexture(font_general->texture);
	
	font_general->text_rect.x = 1423; // coord y ou le texte sera place
	font_general->text_rect.y = 902; // coord y ou le texte sera place
	draw_text(font_general, win, "FlutterShy", 0);
	SDL_DestroyTexture(font_general->texture);
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

void	gui()
{
	t_win		win;
	t_font		font[3];
	SDL_Event	event;
	t_wallpaper	wallpaper;
	t_env		env;

	ft_memset(&env, 0, sizeof(&env));
	env.cycle = 15000; // temporaire
	ft_memset(&win, 0, sizeof(&win));
	ft_memset(&font, 0, sizeof(&font));
	ft_memset(&wallpaper, 0, sizeof(&wallpaper));
	ft_memset(g_memory, 0, MEM_SIZE);
	win.delay = 0;
	font[0].font_size = 15;
	create_window(&win);
	init_ttf(&win);
	select_font(&win, &font[0], "/Library/Fonts/Arial Bold.ttf");
	change_text_color(font[0].text_color, 255, 0, 0);
	font[0].text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte de la memoire sera place
	font[0].text_rect.y = ORIGIN_TEXT_Y; // coord y ou le texte de la memoire sera place
	print_wallpaper(&wallpaper, &win, "./wallpaper/corewar.bmp");
	general_info(font, &win);
	while (42)
	{
		init_env(&env);
		fill_memory();
		SDL_RenderCopy(win.render, wallpaper.texture, NULL, NULL);
		draw_memory(&win, &font[0]);
		write_general_info(&font[1], &env, &win);
		write_challengers(&font[2], &win);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
				break ;
			if (button_press(&event, &wallpaper, &win) == true)
				break ;
		}
		SDL_RenderPresent(win.render);
	}
	TTF_Quit();
	close_window(&win, EXIT_SUCCESS);
}
