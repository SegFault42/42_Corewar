/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:05:56 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/16 14:30:33 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

bool	button_press(SDL_Event *event, t_win *win, t_sdl *sdl)
{
	if (event->type == SDL_MOUSEBUTTONDOWN &&
			event->button.button == SDL_BUTTON_LEFT)
	{
		if (event->button.x >= 1238 && event->button.x <= 1298 &&
			event->button.y >= 1006 && event->button.y <= 1052)
		{
			screenshot(win, sdl);
			Mix_PlayChannel(-1, sdl->sound.chunk, 0);
		}
		if (event->button.x >= 1334 && event->button.x <= 1367 &&
				event->button.y >= 1012 && event->button.y <= 1046)
			win->delay = (win->delay < 90) ? win->delay + 5 : win->delay;
		if (event->button.x >= 1454 && event->button.x <= 1486 &&
				event->button.y >= 1012 && event->button.y <= 1046)
			win->delay = (win->delay > 0) ? win->delay - 5 : win->delay;
	}
	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
		return (true);
	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE)
		win->color = ~win->color;
	return (false);
}

void	print_wallpaper(t_wallpaper *wallpaper, t_win *win, char *path)
{
	wallpaper->wallpaper = SDL_LoadBMP(path);
	wallpaper->texture = SDL_CreateTextureFromSurface(win->render,
			wallpaper->wallpaper);
}

void	screenshot(t_win *win, t_sdl *sdl)
{
	SDL_Surface	*p_screen;
	char		*name;
	time_t		clk;

	clk = time(NULL);
	if (!(name = (char *)ft_memalloc(sizeof(char) * ft_strlen(ctime(&clk)))))
	{
		ft_putendl_fd("Memory allocation failure !", 2);
		exit(-1);
	}
	name = ft_strncat(name, ctime(&clk), 24);
	name = ft_strcat(name, ".bmp");
	p_screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(win->render, NULL, SDL_PIXELFORMAT_ARGB8888
			, p_screen->pixels, p_screen->pitch);
	SDL_SaveBMP(p_screen, name);
	ft_strdel(&name);
	SDL_FreeSurface(p_screen);
	Mix_PlayChannel(-1, sdl->sound.chunk, 0);
}
