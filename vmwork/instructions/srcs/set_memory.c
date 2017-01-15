/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:57:22 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/15 21:30:40 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void		set_mem_uint8(t_process *process, uint16_t index, uint8_t val)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	while (i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val;
}

void		set_mem_uint16(t_process *process, uint16_t index, uint16_t val)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	while (i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val >> 8;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val;
}

void		set_mem_uint32(t_process *process, uint16_t index, uint32_t val)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	while (i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val >> 24;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val >> 16;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val >> 8;
	if (++i >= MEM_SIZE)
		i -= MEM_SIZE;
	g_mem[i] = val;
}
