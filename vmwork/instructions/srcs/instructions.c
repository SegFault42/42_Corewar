/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/19 00:02:41 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	exec_live(t_process *proc)
{
	//A FAIRE
	printf("Exec live for %08X\n", proc->reg[0]);
}

void	exec_ld(t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec ld\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 0);
		reg = src_param(proc, 1, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec ld ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_st(t_process *proc)
{
	uint8_t			val;
	uint16_t		dest;
	t_instruction	*inst;

	printf("Exec st\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1);
		dest = src_param(proc, 1, 1, 0);
		proc->carry = (!val ? 1 : 0);
		dst_param(proc, 1, dest, val);
	}
}

void	exec_add(t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec add\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec add ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

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
		reg = src_param(proc, 1, 2, 0);
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
		reg = src_param(proc, 1, 2, 0);
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
		reg = src_param(proc, 1, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec xor ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_zjmp(t_process *proc)
{
	t_instruction	*inst;

	printf("Exec zjmp\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		proc->pc = inst->val[0]; % MEM_SIZE;
		printf("Exec zjmp ok: proc->pc = %04X, dest %04X\n", proc->pc, dest);
		inst->i = 0;
	}
}

void	exec_sti(t_process *proc)
{
	uint8_t		reg;
	uint16_t	address;

	printf("Exec sti\n");
	reg = src_param(proc, 1, 0, 0);
	if (valid_reg(reg))
	{
		proc->carry = (!(proc->reg[reg]) ? 1 : 0);
		address = src_param(proc, 0, 1, 1) + src_param(proc, 0, 2, 1);
		set_mem_uint32(proc, address % IDX_MOD, proc->reg[reg]);
		printf("Exec sti ok\n");
	}
}
