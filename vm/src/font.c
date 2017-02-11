/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:08:05 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/11 04:50:04 by rabougue         ###   ########.fr       */
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

static void	set_color(t_env *e, t_font *font, int i, double op)
{
	if (e->nb_player > 0 && g_color[i] == e->player_id[0])
		font->text_color = (SDL_Color){0 * op, 255 * op, 0 * op, 255};
	if (e->nb_player > 1 && g_color[i] == e->player_id[1])
		font->text_color = (SDL_Color){255 * op, 0 * op, 255 * op, 255};
	if (e->nb_player > 2 && g_color[i] == e->player_id[2])
		font->text_color = (SDL_Color){0 * op, 215 * op, 255 * op, 255};
	if (e->nb_player > 3 && g_color[i] == e->player_id[3])
		font->text_color = (SDL_Color){255 * op, 255 * op, 0 * op, 255};
	if (i == GREY_TEXT)
		font->text_color = (SDL_Color){155, 155, 155, 255};
	if (i == GREEN_TEXT)
		font->text_color = (SDL_Color){48, 234, 5, 255};
	if (i == PURPLE_TEXT)
		font->text_color = (SDL_Color){255, 0, 255, 255};
	if (i == CYAN_TEXT)
		font->text_color = (SDL_Color){0, 255, 247, 255};
	if (i == YELLOW_TEXT)
		font->text_color = (SDL_Color){252, 243, 0, 255};
}

void		draw_text(t_font *font, t_win *win, char *str, int i)
{
	t_env		*e;
	t_process	*p;
	uint32_t	j;
	double		op;

	j = -1;
	e = get_env();
	op = 1.0;
	while (++j < e->nb_process)
	{
		p = &(e->process[j]);
		if (p->alive && i == (p->start + p->pc) % MEM_SIZE)
		{
			op = 0.5;
			break ;
		}
	}
	set_color(e, font, i, op);
	font->text = TTF_RenderText_Solid(font->font, str, font->text_color);
	font->texture = SurfaceToTexture(win, font);
	SDL_QueryTexture(font->texture, NULL, NULL, &font->text_rect.w, &font->text_rect.h);
	SDL_RenderCopy(win->render, font->texture, NULL, &font->text_rect);
	if (win->color != 0)
		font->text_color = (SDL_Color){rand() % 255, rand() % 255, rand() % 255, 255};
	else
		font->text_color = (SDL_Color){255, 174, 174, 50};
}
