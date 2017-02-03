/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:10:15 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/03 15:27:12 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	player_color(t_env *e, int i)
{
	uint32_t	j;
	t_process	*p;

	j = -1;
	if (g_color[i] == 1)
		ft_putstr("\033[34m");
	else if (g_color[i] == 2)
		ft_putstr("\033[33m");
	else if (g_color[i] == 3)
		ft_putstr("\033[32m");
	else if (g_color[i] == 4)
		ft_putstr("\033[31m");
	while (++j < e->nb_process)
	{
		p = &(e->process[j]);
		if (p->alive && i == (p->start + p->pc) % MEM_SIZE)
			ft_putstr("\033[30;47m");
	}
	ft_putnbr_hex(g_mem[i], 2);
	ft_putstr("\033[0m");
}

void		dump_memory(t_env *e)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		player_color(e, i);
		ft_putchar((i + 1) % BYTES_BY_LINE ? ' ' : '\n');
	}
	printf("Cycle: %d\n", e->cycle);
	printf("Cycles to die: %d / %d\n", e->cur_die, e->cycle_die);
	printf("Lives: %d / %d\n", e->lives, NBR_LIVE);
	printf("Alives: %d\n", e->alives);
	printf("Max check: %d / %d\n", e->check, MAX_CHECKS);
}
