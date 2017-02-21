/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/17 13:26:22 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_players(t_env *e)
{
	uint32_t	i;
	uint32_t	j;
	t_list		*list;
	t_process	*p;

	i = -1;
	list = e->process;
	while (++i < e->nb_player && list)
	{
		e->player[i].live = 0;
		j = -1;
		p = (t_process*)(list->content);
		while (++j < e->player[i].header.prog_size)
		{
			g_mem[p->start + j] = e->player[i].op[j];
			g_color[p->start + j] = e->player_id[i];
		}
		list = list->next;
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
	init_processes(e);
	init_players(e);
}
