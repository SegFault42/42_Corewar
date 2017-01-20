/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:38:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/20 23:16:32 by rabougue         ###   ########.fr       */
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
	SDL_SetRenderDrawColor(win->render, 0, 0, 0, 255);
	SDL_RenderClear(win->render);
}

void	close_window(t_win *win)
{
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	SDL_Quit();
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
	SDL_Event	event;
	uint8_t		red = 55;
	uint8_t		green = 55;
	uint8_t		blue = 55;

	ft_memset(&win, 0, sizeof(&win));
	create_window(&win);
	sdl_clear(&win);
	SDL_SetRenderDrawColor(win.render, red, green, blue, 255);
	sdl_draw_rectangle(&win, 0, 0, WIDTH, HEIGHT);
	while (42)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
				break ;
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) // ferme la fenetre quand on appuie sur echape
			{
				close_window(&win);
				break ;
			}
		}
		SDL_RenderPresent(win.render);
	}
	close_window(&win);
}
