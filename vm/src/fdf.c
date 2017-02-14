/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:40:36 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/14 20:54:39 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_pos	iso(t_env *e, int y, int x)
{
	t_pos	p;
	t_sdl	*sdl;

	sdl = &(e->sdl);
	p.x = (x - y) * 15 + (WIDTH / 2);
	p.y = ((y + x) * 15 + 128 - ((char)(g_mem[y * 64 + x])) / 6) / 2;
	if (g_pc[y * 64 + x])
		p.y -= 64;
	if (e->nb_player > 0 && g_color[y * 64 + x] == e->player_id[0])
		SDL_SetRenderDrawColor(sdl->win.render, 0, 255, 0, 255);
	else if (e->nb_player > 1 && g_color[y * 64 + x] == e->player_id[1])
		SDL_SetRenderDrawColor(sdl->win.render, 255, 0, 255, 255);
	else if (e->nb_player > 2 && g_color[y * 64 + x] == e->player_id[2])
		SDL_SetRenderDrawColor(sdl->win.render, 0, 215, 255, 255);
	else if (e->nb_player > 3 && g_color[y * 64 + x] == e->player_id[3])
		SDL_SetRenderDrawColor(sdl->win.render, 255, 255, 0, 255);
	else
	{
		if (e->sdl.win.color != 0)
			SDL_SetRenderDrawColor(e->sdl.win.render, rand() % 255, rand() % 255, rand() % 255, 255);
		else
			SDL_SetRenderDrawColor(e->sdl.win.render, 255, 255, 255, 255);
	}
	if (e->nb_player > 0 && g_pc[y * 64 + x] == e->player_id[0])
		SDL_SetRenderDrawColor(sdl->win.render, 0, 255 * 0.6, 0, 255);
	else if (e->nb_player > 1 && g_pc[y * 64 + x] == e->player_id[1])
		SDL_SetRenderDrawColor(sdl->win.render, 255 * 0.6, 0, 255 * 0.6, 255);
	else if (e->nb_player > 2 && g_pc[y * 64 + x] == e->player_id[2])
		SDL_SetRenderDrawColor(sdl->win.render, 0, 215 * 0.6, 255 * 0.6, 255);
	else if (e->nb_player > 3 && g_pc[y * 64 + x] == e->player_id[3])
		SDL_SetRenderDrawColor(sdl->win.render, 255 * 0.6, 255 * 0.6, 0, 255);
	return (p);
}

static void	draw_fdf_memory(t_env *e, t_sdl *sdl)
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

void	fdf(t_env *env, t_sdl *sdl)
{
	SDL_SetRenderDrawColor(sdl->win.render, 0, 0, 0, 255);
	SDL_RenderClear(sdl->win.render);
	draw_fdf_memory(env, sdl);
	if (SDL_PollEvent(&(sdl->event)))
	{
		if ((sdl->event).type == SDL_QUIT) // ferme la fenetre si on clique sur la croix
			env->run = 0;
		if (button_press(&(sdl->event), &(sdl->wallpaper), &(sdl->win), sdl) == true)
			env->run = 0;
	}
	SDL_RenderPresent((sdl->win).render);
}
