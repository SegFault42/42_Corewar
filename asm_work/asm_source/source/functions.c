/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 08:29:24 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/27 08:43:49 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int			search(uint8_t opcode, t_op *tab)
{
	uint8_t	guess;
	uint8_t	min;
	uint8_t	max;

	min = 0;
	max = 16;
	guess = (min + max) / 2;
	while (tab[guess].opcode != opcode)
	{
		if (tab[guess].opcode > opcode)
			max = guess - 1;
		else if (tab[guess].opcode < opcode)
			min = guess + 1;
		else
			return (guess);
		guess = (min + max) / 2;
		if (min > max)
			break ;
	}
	if (tab[guess].opcode == opcode)
		return (guess);
	return (-1);
}
