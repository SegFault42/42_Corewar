/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/18 20:58:46 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	exec_live(t_process *proc)
{
	(void)proc;
	//A FAIRE
	printf("Exec live\n");
}

void	exec_ld(t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec ld\n");
	inst = &(proc->inst);
	if (inst->param[0] == T_IND)
	 	val = get_mem_uint32(proc, inst->val[0] % IDX_MOD);
	else
		val = inst->val[0];
	reg = inst->val[1] - 1;
	if (valid_reg(reg))
	{
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec ld ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_st(t_process *proc)
{
	uint8_t			reg;
	uint16_t		address;
	t_instruction	*inst;

	printf("Exec st\n");
	inst = &(proc->inst);
	reg = inst->val[0] - 1;
	if (valid_reg(reg))
	{
		proc->carry = (!(proc->reg[reg]) ? 1 : 0);
		if (inst->param[1] == T_IND)
		{
			address = inst->val[1];
			set_mem_uint32(proc, address % IDX_MOD, proc->reg[reg]);
			printf("Exec st ok\n");
		}
		else if (inst->param[1] == T_REG && valid_reg(inst->val[1] - 1))
		{
			proc->reg[inst->val[1] - 1] = proc->reg[reg];
			printf("Exec st ok: proc->reg[%d] = %08X\n", inst->val[1] - 1, proc->reg[reg]);
		}
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
		reg = store_param(proc, 0, 2, 0);
		val = store_param(proc, 0, 0, 1) + store_param(proc, 0, 1, 1);
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
		reg = store_param(proc, 0, 2, 0);
		val = store_param(proc, 0, 0, 1) - store_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec sub ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_and(t_process *proc)
{
	uint32_t		p1;
	uint32_t		p2;
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	printf("Exec and\n");
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		p1 = store_param(proc, 1, 0, 1);
		p2 = store_param(proc, 1, 1, 1);
		val = p1 & p2;
		reg = store_param(proc, 1, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec sub ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_sti(t_process *proc)
{
	uint8_t		reg;
	uint16_t	address;

	printf("Exec sti\n");
	reg = store_param(proc, 1, 0, 0);
	if (valid_reg(reg))
	{
		proc->carry = (!(proc->reg[reg]) ? 1 : 0);
		address = store_param(proc, 0, 1, 1) + store_param(proc, 0, 2, 1);
		set_mem_uint32(proc, address % IDX_MOD, proc->reg[reg]);
		printf("Exec sti ok\n");
	}
}
