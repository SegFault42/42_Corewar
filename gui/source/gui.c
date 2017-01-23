/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/23 17:54:21 by rabougue         ###   ########.fr       */
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

void	create_window(t_win *win)
{
	if (SDL_Init(SDL_INIT_VIDEO) == ERROR)
		error(INIT_VIDEO_ERROR);

	win->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (win->win == NULL)
		error(CREATE_WINDOW_ERROR);

	win->render = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_SOFTWARE);
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

	y = 0;
	while (y < size_y)
	{
		x = 0;
		while (x < size_x)
		{
			SDL_RenderDrawPoint(win->render, origin_x + x, origin_y + y);
			++x;
		}
		++y;
	}
}

void	text_color(t_font *font, uint8_t r, uint8_t g, uint8_t b)
{
	font->text_color.r = r;
	font->text_color.r = g;
	font->text_color.r = b;
	font->text_color.a = 255;
}

void	draw_memory(t_win *win, t_font *font)
{
	/*int8_t	x;*/
	/*int8_t	y;*/
	/*[>int	w, h = {0};<]*/
	char frag_memory[MEM_SIZE / MEM_SIZE];

	/*y = -1;*/
	/*while (y++ < 64)*/
	/*{*/
		/*x = -1;*/
		/*while (x++ < 64)*/
		/*{*/
			draw_text(font, win, g_memory[MEM_SIZE - 10]);
			/*[>if (!(TTF_SizeText(font->font, "0xFF", &w, &h)))<]*/
				/*[>ft_fprintf(1, "w = %d, h = %d\n", w, h);<]*/
			/*font->text_rect.x += 25;*/
		/*}*/
		/*font->text_rect.y += 25;*/
	/*font->text_rect.x = 0; // coord x ou le texte sera place*/
	/*}*/
	/*font->text_rect.y = 0; // coord y ou le texte sera place*/
}

/*void	fill_memory(t_font *font)*/
/*{*/
	/*for (int i = 0; i < MEM_SIZE; ++i)*/
	/*{*/
		/*font->memory[i] = 'A' + random() % 26;*/
		/*[>font->memory[i] = *ft_itoa_base(font->memory[i], 16);<]*/
	/*}*/
/*}*/

void	gui()
{
	t_win		win;
	t_font		font;
	SDL_Event	event;
	/*char		*itoa_x;*/

	ft_memset(&win, 0, sizeof(&win));
	ft_memset(&font, 0, sizeof(&font));
	/*font.memory = (char *)ft_memalloc(sizeof(char) * MEM_SIZE);*/
	font.font_size = 10;
	create_window(&win);
	sdl_clear(&win, 55, 55, 55);
	init_ttf(&win, &font);
	text_color(&font, 255, 0, 0);
	font.text_rect.x = 0; // coord x ou le texte sera place
	font.text_rect.y = 0; // coord y ou le texte sera place
	/*int x = 0;*/
	while (42)
	{
		/*fill_memory(&font);*/
		/*itoa_x = ft_itoa(x);*/
		sdl_clear(&win, 55, 55, 55);
		/*draw_text(&font, &win, itoa_x);*/
		/*free(itoa_x);*/
		/*SDL_DestroyTexture(font.texture);*/
		/*++x;*/
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
				break ;
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) // ferme la fenetre quand on appuie sur echape
			{
				break ;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
				sdl_clear(&win, 255, 0, 0);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
				sdl_clear(&win, 0, 255, 0);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
				sdl_clear(&win, 0, 0, 255);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
				sdl_clear(&win, 55, 55, 55);
			ft_fprintf(1, "X ");
		}
		draw_memory(&win, &font);
		SDL_DestroyTexture(font.texture);
		SDL_RenderPresent(win.render);
	}
	TTF_Quit();
	close_window(&win, EXIT_SUCCESS);
}
