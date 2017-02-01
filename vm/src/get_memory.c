/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:21:56 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/01 18:15:51 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint8_t		get_mem_uint8(t_process *process, uint16_t index)
{
	uint32_t	i;

	i = process->start + process->pc + index;
	return (g_mem[i % MEM_SIZE]);
}

uint16_t	get_mem_uint16(t_process *process, uint16_t index)
{
	uint32_t	i;
	uint16_t	val;

	i = process->start + process->pc + index;
	val = g_mem[i % MEM_SIZE] << 8;
	// ft_printf("get_mem_uint16[%x]: val1 = %x", i, g_mem[i % MEM_SIZE]);
	i++;
	// ft_printf(", val2 = %x, val = %x\n", g_mem[i % MEM_SIZE], val + g_mem[i % MEM_SIZE]);
	return (val + g_mem[i % MEM_SIZE]);
}

uint32_t	get_mem_uint32(t_process *process, uint16_t index)
{
	uint32_t	i;
	uint32_t	val;

	i = process->start + process->pc + index;
	val = g_mem[i % MEM_SIZE] << 24;
	i++;
	val += g_mem[i % MEM_SIZE] << 16;
	i++;
	val += g_mem[i % MEM_SIZE] << 8;
	i++;
	return (val + g_mem[i % MEM_SIZE]);
}
