/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 22:36:40 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/16 15:47:09 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	create_window(t_win *win)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == ERROR)
		error(INIT_VIDEO_ERROR);
	IMG_Init(IMG_INIT_PNG);
	win->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (win->win == NULL)
		error(CREATE_WINDOW_ERROR);
	win->render = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_SOFTWARE);
}

void	init_ttf(t_win *win)
{
	if (TTF_Init() == ERROR)
	{
		ft_fprintf(2, RED"%s\n"END, TTF_GetError());
		close_window(win, ERROR);
	}
}

void	init_sdl_gui(t_sdl *sdl)
{
	ft_memset(&(sdl->win), 0, sizeof(&(sdl->win)));
	ft_memset(&(sdl->font), 0, sizeof(&(sdl->font)));
	ft_memset(&(sdl->wallpaper), 0, sizeof(&(sdl->wallpaper)));
	ft_memset(&(sdl->wallpaper), 0, sizeof(&(sdl->sound)));
	(sdl->win).delay = 0;
	(sdl->font)[0].font_size = 15;
	create_window(&(sdl->win));
	init_ttf(&(sdl->win));
	init_sound(&(sdl->sound));
	select_font(&(sdl->win), &(sdl->font)[0], "/Library/Fonts/Arial Bold.ttf");
	change_text_color((sdl->font)[0].text_color, 255, 0, 0);
	(sdl->font)[0].text_rect.x = ORIGIN_TEXT_X;
	(sdl->font)[0].text_rect.y = ORIGIN_TEXT_Y;
	print_wallpaper(&(sdl->wallpaper), &(sdl->win), "./wallpaper/corewar.bmp");
	general_info((sdl->font), &(sdl->win));
}

void	init_sdl_fdf(t_sdl *sdl)
{
	ft_memset(&(sdl->win), 0, sizeof(&(sdl->win)));
	create_window(&(sdl->win));
}
