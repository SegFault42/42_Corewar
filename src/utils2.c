/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:43:35 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/03 15:30:47 by qhonore          ###   ########.fr       */
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

bool	valid_reg(uint8_t reg)
{
	if (reg >= 0 && reg < REG_NUMBER)
		return (1);
	return (0);
}

int		get_address(int val)
{
	if (val >= ADDRESS_MAX / 2)
		val -= ADDRESS_MAX;
	return (val);
}

int		mem_address(int val)
{
	if (val >= ADDRESS_MAX / 2)
		val -= ADDRESS_MAX;
	val %= MEM_SIZE;
	return (val);
}

int		idx_address(int val)
{
	if (val >= ADDRESS_MAX / 2)
		val -= ADDRESS_MAX;
	val %= IDX_MOD;
	return (val);
}
