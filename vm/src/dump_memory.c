/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:10:15 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/11 23:51:33 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	player_color(t_env *e, int i)
{
	uint32_t	j;

	j = -1;
	if (e->nb_player > 0 && g_pc[i] == e->player_id[0])
		ft_putstr("\033[39;48;5;29m");
	else if (e->nb_player > 1 && g_pc[i] == e->player_id[1])
		ft_putstr("\033[39;48;5;55m");
	else if (e->nb_player > 2 && g_pc[i] == e->player_id[2])
		ft_putstr("\033[39;48;5;88m");
	else if (e->nb_player > 3 && g_pc[i] == e->player_id[3])
		ft_putstr("\033[39;48;5;202m");
	else
	{
		if (e->nb_player > 0 && g_color[i] == e->player_id[0])
			ft_putstr("\033[38;5;29m");
		else if (e->nb_player > 1 && g_color[i] == e->player_id[1])
			ft_putstr("\033[38;5;55m");
		else if (e->nb_player > 2 && g_color[i] == e->player_id[2])
			ft_putstr("\033[38;5;88m");
		else if (e->nb_player > 3 && g_color[i] == e->player_id[3])
			ft_putstr("\033[38;5;208m");
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
	ft_printf("Cycle totaux: %d\n", e->cycle);
	ft_printf("Cycles to die: %d / %d\n", e->cur_die, e->cycle_die);
	ft_printf("Lives: %d(%d) / %d\n", e->lives, e->valid_lives, NBR_LIVE);
	ft_printf("Processes alives: %d / %d\n", e->alives, e->nb_process);
	ft_printf("Max check: %d / %d\n", e->check, MAX_CHECKS);
	ft_printf("Last live -> Player %d\n", e->last_live);
}
