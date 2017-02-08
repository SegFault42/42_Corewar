/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:08:05 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/08 12:48:10 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		select_font(t_win *win, t_font *font, char *str)
{
	font->font = TTF_OpenFont(str, font->font_size);
	if (font->font == NULL)
	{
		ft_printf("{:red}%s{:eoc}\n", TTF_GetError());
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
	t_env	*e;

	e = get_env();
	if (e->nb_player > 0 && g_color[i] == e->player_id[0])
		font->text_color = (SDL_Color){0, 255, 0, 255};
	if (e->nb_player > 1 && g_color[i] == e->player_id[1])
		font->text_color = (SDL_Color){255, 0, 255, 255};
	if (e->nb_player > 2 && g_color[i] == e->player_id[2])
		font->text_color = (SDL_Color){0, 215, 255, 0};
	if (e->nb_player > 3 && g_color[i] == e->player_id[3])
		font->text_color = (SDL_Color){255, 255, 0, 255};
	/*else*/
		/*font->text_color = (SDL_Color){255, 255, 255, 255};*/
	font->text = TTF_RenderText_Solid(font->font, str, font->text_color);
	font->texture = SurfaceToTexture(win, font);
	/*font->text_rect.x = 500; // coord x ou le texte sera place*/
	/*font->text_rect.y = 500; // coord y ou le texte sera place*/
	SDL_QueryTexture(font->texture, NULL, NULL, &font->text_rect.w, &font->text_rect.h);
	SDL_RenderCopy(win->render, font->texture, NULL, &font->text_rect);
	font->text_color = (SDL_Color){174, 174, 174, 255};
}
