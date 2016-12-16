/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 21:02:27 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/16 18:12:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include "libft.h"

static void		ft_putnbr_hex(int octet, int rem)
{
		char const *base = "0123456789abcdef";

		if (rem > 1)
				ft_putnbr_hex(octet >> 4, rem - 1);
		write(1, base + (octet % 16), 1);
}

static void		sp_putchar(char const *ptr)
{
		char const c = *ptr;

		if (c >= ' ' && c <= '~')
				write(1, &c, 1);
		else
				write(1, ".", 1);
}

static void		print_number(const unsigned char *addr,
				size_t size, size_t i)
{
		int a;

		a = 0;
		while (a < 16 && a + i < size)
		{
				ft_putnbr_hex(*(addr + i + a), 2);
				write(1, " ", 1);
				if (a == 7)
					write(1, " ", 1);
				++a;
		}
		if (a < 16)
			write(1, " ", 1);
		while (a < 16)
		{
				write(1, "   ", 3);
				++a;
		}
}

static void		print_characters(const char *addr,
				size_t size, size_t i)
{
		int a;

		a = 0;
		write(1, "|", 1);
		while (a < 16 && a + i < size)
		{
				sp_putchar(addr + a + i);
				a++;
		}
		write(1, "|", 1);
}

void			print_memory(const void *addr, size_t size)
{
		size_t i;

		i = 0;
		while (i < size)
		{
				ft_printf("%d	", i);
				print_number((const unsigned char *)addr, size, i);
				print_characters((const char *)addr, size, i);
				write(1, "\n", 1);
				i += 16;
		}
}
