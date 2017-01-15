/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:10:15 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/15 17:28:05 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

static void		ft_putnbr_hex(int octet, int rem)
{
		char const *base = "0123456789abcdef";

		if (rem > 1)
				ft_putnbr_hex(octet >> 4, rem - 1);
		write(1, base + (octet % 16), 1);
}

void	dump_memory(t_process *proc)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == proc->start + proc->pc + proc->inst.i)
			ft_putstr("\033[47m");
		ft_putnbr_hex(g_mem[i], 2);
		if (i == proc->start + proc->pc + proc->inst.i)
			ft_putstr("\033[0m");
		ft_putchar((i + 1) % 64 ? ' ' : '\n');
	}
}
