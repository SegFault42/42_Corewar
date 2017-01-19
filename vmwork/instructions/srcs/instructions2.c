/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/19 18:54:51 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	exec_sub(t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec sub\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) - src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec sub ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_and(t_process *proc)
{
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	printf("Exec and\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1) & src_param(proc, 1, 1, 1);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec and ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_or(t_process *proc)
{
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	printf("Exec or\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1) | src_param(proc, 1, 1, 1);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec or ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_xor(t_process *proc)
{
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	printf("Exec xor\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1) ^ src_param(proc, 1, 1, 1);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec xor ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}
