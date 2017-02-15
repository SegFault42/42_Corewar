/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 14:11:01 by rabougue         ###   ########.fr       */
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
	if (e->nb_player > MAX_PLAYERS)
	{
		ft_putendl_fd("Max player : 4", 2);
		exit(EXIT_FAILURE);
	}
	e->nb_process = e->nb_player;
	e->alives = e->nb_player;
	ft_load(fd, e);
	if (!(e->process = (t_process*)malloc(sizeof(t_process) * e->nb_process)))
		die(e, "malloc failure (e->process)");
	init_processes(e);
	init_players(e);
}
