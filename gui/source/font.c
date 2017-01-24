/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:08:05 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/24 17:36:11 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void		init_ttf(t_win *win, t_font *font)
{
	if (TTF_Init() == ERROR)
	{
		ft_fprintf(2, "%s\n", TTF_GetError());
		close_window(win, ERROR);
	}
	font->font = TTF_OpenFont("./font/monaco.ttf", font->font_size);
	if (font->font == NULL)
	{
		ft_fprintf(2, "%s\n", TTF_GetError());
		TTF_Quit();
		close_window(win, ERROR);
	}
}

SDL_Texture	*SurfaceToTexture(t_win *win, t_font *font)
{
	SDL_Texture	*text;

	text = SDL_CreateTextureFromSurface(win->render, font->text);
	SDL_FreeSurface(font->text);
	return (text);
}

void		draw_text(t_font *font, t_win *win, char *str, int i)
{
	if (g_memory_color[i] == 1)
		font->text_color = (SDL_Color){40, 255, 0, 255};
	else if (g_memory_color[i] == 2)
		font->text_color = (SDL_Color){255, 0, 215, 255};
	else if (g_memory_color[i] == 3)
		font->text_color = (SDL_Color){0, 0, 181, 232};
	else if (g_memory_color[i] == 4)
		font->text_color = (SDL_Color){0, 255, 255, 255};
	else
		font->text_color = (SDL_Color){255, 255, 255, 255};
	font->text = TTF_RenderText_Solid(font->font, str, font->text_color);
	font->texture = SurfaceToTexture(win, font);
	/*font->text_rect.x = 500; // coord x ou le texte sera place*/
	/*font->text_rect.y = 500; // coord y ou le texte sera place*/
	SDL_QueryTexture(font->texture, NULL, NULL, &font->text_rect.w, &font->text_rect.h);
	SDL_RenderCopy(win->render, font->texture, NULL, &font->text_rect);
}
