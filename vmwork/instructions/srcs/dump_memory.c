/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:10:15 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/21 00:54:22 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

static void	ft_putnbr_hex(int octet, int rem)
{
		char const *base = "0123456789abcdef";

		if (rem > 1)
				ft_putnbr_hex(octet >> 4, rem - 1);
		write(1, base + (octet % 16), 1);
}

static void	player_color(t_env *e, int i)
{
	if (g_color[i] == 1)
		ft_putstr("\033[34m");
	else if (g_color[i] == 2)
		ft_putstr("\033[33m");
	else if (g_color[i] == 3)
		ft_putstr("\033[32m");
	else if (g_color[i] == 4)
		ft_putstr("\033[31m");
	// if ()JENETELA
	(void)e;
	ft_putnbr_hex(g_mem[i], 2);
	ft_putstr("\033[0m");
}

void		dump_memory(t_env *e)
{
	int		i;

	i = -1;
	// ft_putstr("\033[1;1H\033[2J");
	(void)e;
	while (++i < MEM_SIZE)
	{
		player_color(e, i);
		ft_putchar((i + 1) % 64 ? ' ' : '\n');
	}
}
