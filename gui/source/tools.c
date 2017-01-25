/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:05:56 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/25 22:21:32 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	print_wallpaper(t_wallpaper *wallpaper, t_win *win)
{
	wallpaper->wallpaper = SDL_LoadBMP("./wallpaper/corewar.bmp");
	wallpaper->texture = SDL_CreateTextureFromSurface(win->render, wallpaper->wallpaper);
}

void	screenshot(t_win *win)
{
	SDL_Surface	*p_screen;
	static int	number_screen = 0;
	char		*name;
	char		*num;
	char		test[16];

	ft_strcpy(test, "Screenshot");
	num = ft_itoa(number_screen);
	name = ft_strcat(test, num);
	free(num);
	name = ft_strcat(name, ".bmp");
	p_screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT,
			32, 0, 0, 0, 0);
	SDL_RenderReadPixels(win->render, NULL, SDL_PIXELFORMAT_ARGB8888
			, p_screen->pixels, p_screen->pitch);
	SDL_SaveBMP(p_screen, name);
	SDL_FreeSurface(p_screen);
	/*Mix_PlayChannel(-1, win->chunk, 0);*/
	++number_screen;
}
