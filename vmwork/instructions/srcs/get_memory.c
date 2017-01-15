/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:21:56 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/15 20:22:41 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

uint8_t		get_mem_uint8(t_process *process, uint16_t index)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	while (i >= MEM_SIZE)
		i -= MEM_SIZE;
	return (g_mem[i]);
}

uint16_t	get_mem_uint16(t_process *process, uint16_t index)
{
	uint32_t	i;
	uint16_t	val;

	i = process->start + process->pc + index;
	while (i >= MEM_SIZE)
		i -= MEM_SIZE;
	val = g_mem[i] << 8;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	return (val + g_mem[i]);
}

uint32_t	get_mem_uint32(t_process *process, uint16_t index)
{
	uint32_t	i;
	uint32_t	val;

	i = process->start + process->pc + index;
	while (i >= MEM_SIZE)
		i -= MEM_SIZE;
	val = g_mem[i] << 24;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	val += g_mem[i] << 16;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	val += g_mem[i] << 8;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	return (val + g_mem[i]);
}
