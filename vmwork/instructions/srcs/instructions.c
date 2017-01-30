/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/18 01:37:29 by qhonore          ###   ########.fr       */
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
	if (reg >= 0 && reg < REG_NUMBER)
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
	if (reg >= 0 && reg < REG_NUMBER)
	{
		proc->carry = (!(proc->reg[reg]) ? 1 : 0);
		if (inst->param[1] == T_IND)
		{
			address = inst->val[1];
			set_mem_uint32(proc, address % IDX_MOD, proc->reg[reg]);
			printf("Exec st ok\n");
		}
		else if (inst->val[1] - 1 < REG_NUMBER)
		{
			proc->reg[inst->val[1] - 1] = proc->reg[reg];
			printf("Exec st ok: proc->reg[%d] = %08X\n", inst->val[1] - 1, proc->reg[reg]);
		}
	}
}

void	exec_sti(t_process *proc)
{
	uint8_t		reg;
	uint16_t	address;

	printf("Exec sti\n");
	reg = proc->inst.val[0] - 1;
	if (reg >= 0 && reg < REG_NUMBER)
	{
		proc->carry = (!(proc->reg[reg]) ? 1 : 0);
		address = proc->inst.val[1] + proc->inst.val[2];
		set_mem_uint32(proc, address % IDX_MOD, proc->reg[reg]);
		printf("Exec sti ok\n");
	}
}
