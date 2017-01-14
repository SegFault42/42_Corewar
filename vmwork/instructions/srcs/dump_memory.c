/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:10:15 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/12 19:10:50 by qhonore          ###   ########.fr       */
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

void	dump_memory(void)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		ft_putnbr_hex(g_mem[i], 2);
		ft_putchar((i + 1) % 64 ? ' ' : '\n');
	}
}
