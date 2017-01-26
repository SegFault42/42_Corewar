/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/26 23:28:29 by rabougue         ###   ########.fr       */
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
			/*font->text_color = (SDL_Color){255, 0, 255, 255};*/
			draw_text(font, win, memory, i);
			free(memory);
			SDL_DestroyTexture(font->texture);
			/*free(frag_memory[i]);*/
			/*if (!(TTF_SizeText(font->font, "0xFF", &w, &h)))*/
				/*ft_fprintf(1, "w = %d, h = %d\n", w, h);*/
			font->text_rect.x += INCR_TEXT_X;
			++i;
		}
		font->text_rect.y += INCR_TEXT_Y;
		font->text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte sera place
	}
	font->text_rect.y = 1000; // coord y ou le texte sera place
	font->text_rect.x = 1000; // coord y ou le texte sera place
	/*font->font = TTF_OpenFont("/Library/Fonts/AmericanTypewriter.ttc", font->font_size);*/
	/*font->font_size = 50;*/
	/*draw_text(font, win, ft_itoa(win->delay), 5);*/
	/*font->font_size = 15;*/
	/*font->font = TTF_OpenFont("/Library/Fonts/Arial Bold.ttf", font->font_size);*/
	font->text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte sera place
	font->text_rect.y = ORIGIN_TEXT_Y; // coord y ou le texte sera place
}

void	fill_memory()
{
	int i = 0;

	while (i < MEM_SIZE)
	{
		g_memory[i] = 'A' + random() % 26;
		/*g_memory[i] = i;*/
		/*font->memory[i] = *ft_itoa_base(font->memory[i], 16);*/
		/*printf("%d\n", i);*/
		++i;
	}
	i = 0;
	while (i < 50)
	{
		g_memory_color[i + random() % MEM_SIZE] = 1;
		g_memory_color[i + random() % MEM_SIZE] = 2;
		g_memory_color[i + random() % MEM_SIZE] = 3;
		g_memory_color[i +random() % MEM_SIZE] = 4;
		++i;
	}
}

static void init_env(t_env *env)
{
	env->nb_player = 2;
	env->nb_process = random() % 50;
	env->cur_process = random() % 50;
	env->cycle -= 20;
}

void	draw_general_info(t_win *win, t_env *env)
{
	// ouvrir le font une seul fois
	t_font	font_general;
	char	*cycle;

	cycle = ft_itoa(env->cycle);
	ft_memset(&font_general, 0, sizeof(t_font));
	font_general.font_size = 140;
	font_general.font_size = 15;
	select_font(win, &font_general, "/Library/Fonts/Arial Bold.ttf");
	font_general.text_rect.x = 1325; // coord y ou le texte sera place
	font_general.text_rect.y = 30; // coord y ou le texte sera place
	font_general.text_color = (SDL_Color){174, 174, 174, 255};
	draw_text(&font_general, win, "Cycle = ", 0);
	font_general.text_rect.x = 1385; // coord y ou le texte sera place
	draw_text(&font_general, win, cycle, 0);
	free(cycle);
	SDL_DestroyTexture(font_general.texture);
}

void	gui()
{
	t_win		win;
	t_font		font;
	SDL_Event	event;
	t_wallpaper	wallpaper;
	t_env		env;
	/*int8_t		r = 55, g = 55, b = 55;*/
	/*char		*itoa_x;*/
	/*SDL_Renderer	*wallpaper = SDL_CreateRenderer(win.win, -1, 0);*/

	ft_memset(&env, 0, sizeof(&env));
	env.cycle = 15000;
	ft_memset(&win, 0, sizeof(&win));
	ft_memset(&font, 0, sizeof(&font));
	ft_memset(&font, 0, sizeof(&wallpaper));
	ft_memset(g_memory, 0, MEM_SIZE);
	win.delay = 0;
	/*font.memory = (char *)ft_memalloc(sizeof(char) * MEM_SIZE);*/
	font.font_size = 15;
	create_window(&win);
	sdl_clear(&win, 55, 55, 55);
	init_ttf(&win);
	select_font(&win, &font, "/Library/Fonts/Arial Bold.ttf");
	change_text_color(font.text_color, 255, 0, 0);
	font.text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte sera place
	font.text_rect.y = ORIGIN_TEXT_Y; // coord y ou le texte sera place
	/*SDL_Rect dstrect = { 0, 0, 1920, 1080 };*/
	/*int x = 0;*/
	print_wallpaper(&wallpaper, &win, "./wallpaper/corewar.bmp");
	while (42)
	{
		init_env(&env);
		/*win.g_screen_surface = SDL_GetWindowSurface(win.win);*/
		/*print_wallpaper(&win);*/
		fill_memory();
		SDL_RenderCopy(win.render, wallpaper.texture, NULL, NULL);
		/*itoa_x = ft_itoa(x);*/
			/*sdl_clear(&win, r, g, b);*/
		/*draw_text(&font, &win, itoa_x);*/
		/*free(itoa_x);*/
		/*SDL_DestroyTexture(font.texture);*/
		/*++x;*/
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
				break ;
			/*button_press(&event, &wallpaper, &win);*/
			/*ft_fprintf(1, "X ");*/
		}
		if (button_press(&event, &wallpaper, &win) == true)
			break ;
		draw_memory(&win, &font);
		draw_general_info(&win, &env);
		SDL_RenderPresent(win.render);
	}
	TTF_Quit();
	close_window(&win, EXIT_SUCCESS);
}
