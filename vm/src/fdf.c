/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:40:36 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/15 20:04:46 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		change_colors(t_env *e, SDL_Renderer *render,\
														uint32_t val, bool roll)
{
	if (e->nb_player > 0 && val == e->player_id[0])
		SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	else if (e->nb_player > 1 && val == e->player_id[1])
		SDL_SetRenderDrawColor(render, 255, 0, 255, 255);
	else if (e->nb_player > 2 && val == e->player_id[2])
		SDL_SetRenderDrawColor(render, 0, 215, 255, 255);
	else if (e->nb_player > 3 && val == e->player_id[3])
		SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
	else if (roll)
	{
		if (e->sdl.win.color != 0)
			SDL_SetRenderDrawColor(render, rand() % 255, rand() % 255,\
															rand() % 255, 255);
		else
			SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	}
}

static t_pos	iso(t_env *e, int y, int x)
{
	t_pos	p;
	t_sdl	*sdl;

	sdl = &(e->sdl);
	p.x = (x - y) * 10 + (655);
	p.y = ((y + x) * 10 + 300 - ((char)(g_mem[y * 64 + x])) / 6) / 2;
	if (g_pc[y * 64 + x])
		p.y -= 64;
	change_colors(e, sdl->win.render, g_color[y * 64 + x], 1);
	change_colors(e, sdl->win.render, g_pc[y * 64 + x], 0);
	return (p);
}

static void		draw_fdf_memory(t_env *e, t_sdl *sdl)
{
	int		y;
	int		x;
	t_pos	p1;
	t_pos	p2;

	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			p1 = iso(e, y, x);
			p2 = iso(e, y, x - 1);
			if (x - 1 >= 0)
				SDL_RenderDrawLine(sdl->win.render, p1.x, p1.y, p2.x, p2.y);
			p2 = iso(e, y - 1, x);
			if (y - 1 >= 0)
				SDL_RenderDrawLine(sdl->win.render, p1.x, p1.y, p2.x, p2.y);
		}
	}
}

void			fdf(t_env *env, t_sdl *sdl)
{
	SDL_RenderCopy((sdl->win).render, (sdl->wallpaper).texture, NULL, NULL);
	draw_fdf_memory(env, sdl);
	write_general_info(&(sdl->font[1]), env, &(sdl->win));
	write_challengers(&(sdl->font[2]), &(sdl->win));
	if (SDL_PollEvent(&(sdl->event)))
	{
		if ((sdl->event).type == SDL_QUIT)
			env->run = 0;
		if (button_press(&(sdl->event), &(sdl->win), sdl))
			env->run = 0;
	}
	SDL_RenderPresent((sdl->win).render);
}
