/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 22:36:40 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/04 20:30:20 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	create_window(t_win *win)
{
	if (SDL_Init(SDL_INIT_VIDEO) == ERROR)
		error(INIT_VIDEO_ERROR);

	IMG_Init(IMG_INIT_PNG);
	win->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	if (win->win == NULL)
		error(CREATE_WINDOW_ERROR);

	win->render = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_SOFTWARE);
}

void		init_ttf(t_win *win)
{
	if (TTF_Init() == ERROR)
	{
		ft_printf("{:red}%s{:eoc}\n", TTF_GetError());
		close_window(win, ERROR);
	}
}
