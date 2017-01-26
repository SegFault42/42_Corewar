/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:05:56 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/26 21:46:01 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	button_press(SDL_Event *event, t_wallpaper *wallpaper, t_win *win)
{

	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
	{
		if (event->button.x >= 1334 && event->button.x <= 1367 && event->button.y >= 1012 && event->button.y <= 1046)
		{
			if (win->delay < 200)
				win->delay += 10;
			printf("%d\n", win->delay);
		}
		if (event->button.x >= 1454 && event->button.x <= 1486 && event->button.y >= 1012 && event->button.y <= 1046)
		{
			if (win->delay > 0)
				win->delay -= 10;
			printf("%d\n", win->delay);
		}
		/*else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_p)*/
			/*screenshot(&win);*/
	}
	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE) // ferme la fenetre quand on appuie sur echape
		return (true);
	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE)
		SDL_Delay(win->delay);
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
