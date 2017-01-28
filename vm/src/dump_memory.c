/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:10:15 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/28 16:43:20 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_putnbr_hex(int octet, int rem)
{
		char const *base = "0123456789abcdef";

		if (rem > 1)
				ft_putnbr_hex(octet >> 4, rem - 1);
		write(1, base + (octet % 16), 1);
}

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
		if (e->player[p->player_id].alive && i == (p->start + p->pc) % MEM_SIZE)
			ft_putstr("\033[30;47m");
	}
	ft_putnbr_hex(g_mem[i], 2);
	ft_putstr("\033[0m");
}

static void	player_info(t_env *e)
{
	uint32_t	i;
	t_player	*player;
	t_process	*proc;

	i = -1;
	while (++i < e->nb_player)
	{
		player = &(e->player[i]);
		proc = &(e->process[i]);
		printf("P%d: live(%d), carry(%d)", i, player->live, proc->carry);
		printf(", reg(1:%08X, 2:%08X, 3:%08X, 4:%08X, 5:%08X, 6:%08X, 7:%08X, 8:%08X", proc->reg[0], proc->reg[1], proc->reg[2], proc->reg[3], proc->reg[4], proc->reg[5], proc->reg[6], proc->reg[7]);
		printf(", 9:%08X, 10:%08X, 11:%08X, 12:%08X, 13:%08X, 14:%08X, 15:%08X, 16:%08X)\n", proc->reg[8], proc->reg[9], proc->reg[10], proc->reg[11], proc->reg[12], proc->reg[13], proc->reg[14], proc->reg[15]);
	}
}

void		dump_memory(t_env *e)
{
	int		i;

	i = -1;
	ft_putstr("\033[1;1H\033[2J");
	(void)e;
	while (++i < MEM_SIZE)
	{
		player_color(e, i);
		ft_putchar((i + 1) % 64 ? ' ' : '\n');
	}
	player_info(e);
	printf("Cycle: %d\n", e->cycle);
	printf("Cycles to die: %d / %d\n", e->cur_die, e->cycle_die);
	printf("Lives: %d / %d\n", e->lives, NBR_LIVE);
	printf("Alives: %d\n", e->alives);
	printf("Max check: %d / %d\n", e->check, MAX_CHECKS);
}
