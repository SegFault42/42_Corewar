/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:57:22 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/16 15:00:20 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void		set_mem_uint8(t_process *process, uint16_t index, uint8_t val)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	g_mem[i % MEM_SIZE] = val;
}

void		set_mem_uint16(t_process *process, uint16_t index, uint16_t val)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	g_mem[i % MEM_SIZE] = val >> 8;
	i++;
	g_mem[i % MEM_SIZE] = val;
}

void		set_mem_uint32(t_process *process, uint16_t index, uint32_t val)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	g_mem[i % MEM_SIZE] = val >> 24;
	i++;
	g_mem[i % MEM_SIZE] = val >> 16;
	i++;
	g_mem[i % MEM_SIZE] = val >> 8;
	i++;
	g_mem[i % MEM_SIZE] = val;
}
