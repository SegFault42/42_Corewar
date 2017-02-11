/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:05:56 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/11 04:52:49 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

bool	button_press(SDL_Event *event, t_wallpaper *wallpaper, t_win *win)
{
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		if (event->button.x >= 1238 && event->button.x <= 1298 &&
			event->button.y >= 1006 && event->button.y <= 1052)
			screenshot(win);
	}
	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE) // ferme la fenetre quand on appuie sur echape
		return (true);
	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE)
		win->color = ~win->color;
	SDL_Delay(win->delay);
	return (false);
	(void)wallpaper;
}

void	print_wallpaper(t_wallpaper *wallpaper, t_win *win, char *path)
{
	wallpaper->wallpaper = SDL_LoadBMP(path);
	wallpaper->texture = SDL_CreateTextureFromSurface(win->render, wallpaper->wallpaper);
}

void	screenshot(t_win *win)
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
	/*Mix_PlayChannel(-1, win->chunk, 0);*/
}
