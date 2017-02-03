/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/03 17:29:32 by qhonore          ###   ########.fr       */
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
			g_color[e->process[i].start + j] = i + 1;
		}
	}
}

int		init_vm(t_env *e, int argc, char **argv)
{
	uint8_t	fd[MAX_PLAYERS];

	if ((e->nb_player = ft_parse(e, argc, argv, fd)) < 1)
		return (0);
	e->nb_process = e->nb_player;
	ft_load(fd, e);
	if (!(e->process = (t_process*)malloc(sizeof(t_process) * e->nb_process)))
		die(e, "malloc failure (e->process)");
	init_processes(e);
	init_players(e);
	return (1);
}
