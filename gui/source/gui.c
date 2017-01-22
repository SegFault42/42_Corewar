/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/21 19:30:58 by rabougue         ###   ########.fr       */
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

void	sdl_clear(t_win *win)
{
	SDL_SetRenderDrawColor(win->render, 55, 55, 55, 255);
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

void	gui()
{
	t_win		win;
	t_font		font;
	SDL_Event	event;

	ft_memset(&win, 0, sizeof(&win));
	ft_memset(&font, 0, sizeof(&font));
	create_window(&win);
	sdl_clear(&win);
	init_ttf(&win, &font);
	while (42)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
				break ;
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) // ferme la fenetre quand on appuie sur echape
			{
				break ;
			}
		}
		SDL_RenderPresent(win.render);
	}
	TTF_Quit();
	close_window(&win, EXIT_SUCCESS);
}
