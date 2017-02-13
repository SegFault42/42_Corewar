/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_byte_inst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:09:04 by jcazako           #+#    #+#             */
/*   Updated: 2017/02/13 21:48:44 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "functions.h"

static void	help(char **param, int *byte, char opcode)
{
	while (param && *param)
	{
		if (is_reg(*param))
			(*byte)++;
		else if (is_direct(*param))
		{
			if (opcode == ZJUMP || opcode == LDI
				|| opcode == STI || opcode == FORK
				|| opcode == LLDI || opcode == LFORK)
				(*byte) += 2;
			else
				(*byte) += 4;
		}
		else if (is_ind(*param))
			(*byte) += 2;
		param++;
	}
}

int			count_byte_inst(t_info *info)
{
	int		byte;
	char	**param;
	char	opcode;

	byte = 0;
	if (info && (opcode = info->opcode) > 0)
	{
		byte++;
		if (opcode != LIVE && opcode != ZJUMP && opcode != FORK)
			byte++;
		param = info->param;
		help(param, &byte, opcode);
	}
	return (byte);
}
