/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/12 04:49:08 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_players(t_env *e)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < e->nb_player)
	{
		e->player[i].live = 0;
		j = -1;
		while (++j < e->player[i].header.prog_size)
		{
			g_mem[e->process[i].start + j] = e->player[i].op[j];
			g_color[e->process[i].start + j] = e->player_id[i];
		}
	}
}

void	init_vm(t_env *e, int argc, char **argv)
{
	uint8_t	fd[MAX_PLAYERS];

	if ((e->nb_player = ft_parse(e, argc, argv, fd)) < 1)
		die(e, "Please give a file to load!");
	e->nb_process = e->nb_player;
	e->alives = e->nb_player;
	ft_load(fd, e);
	if (!(e->process = (t_process*)malloc(sizeof(t_process) * e->nb_process)))
		die(e, "malloc failure (e->process)");
	init_processes(e);
	init_players(e);
}

void	init_sdl(t_sdl *sdl)
{
	// ft_memset(&env, 0, sizeof(&env));
	// env.cycle = 15000; // temporaire
	ft_memset(&(sdl->win), 0, sizeof(&(sdl->win)));
	ft_memset(&(sdl->font), 0, sizeof(&(sdl->font)));
	ft_memset(&(sdl->wallpaper), 0, sizeof(&(sdl->wallpaper)));
	ft_memset(&(sdl->wallpaper), 0, sizeof(&(sdl->sound)));
	// ft_memset(g_mem, 0, MEM_SIZE);
	(sdl->win).delay = 0;
	(sdl->font)[0].font_size = 15;
	create_window(&(sdl->win));
	init_ttf(&(sdl->win));
	init_sound(&(sdl->sound));
	select_font(&(sdl->win), &(sdl->font)[0], "/Library/Fonts/Arial Bold.ttf");
	change_text_color((sdl->font)[0].text_color, 255, 0, 0);
	(sdl->font)[0].text_rect.x = ORIGIN_TEXT_X; // coord x ou le texte de la memoire sera place
	(sdl->font)[0].text_rect.y = ORIGIN_TEXT_Y; // coord y ou le texte de la memoire sera place
	print_wallpaper(&(sdl->wallpaper), &(sdl->win), "./wallpaper/corewar.bmp");
	general_info((sdl->font), &(sdl->win));
}
