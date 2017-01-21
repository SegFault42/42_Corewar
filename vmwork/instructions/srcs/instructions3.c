/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/21 20:43:10 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	exec_zjmp(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	printf("Exec zjmp\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		proc->pc = (proc->pc + inst->val[0]) % MEM_SIZE;
		printf("Exec zjmp ok: proc->pc = %04X\n", proc->pc);
	}
}

void	exec_ldi(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint16_t		address;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec ldi\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		address = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		val = get_mem_uint32(proc, address % IDX_MOD);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec ldi ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_sti(t_env *e, t_process *proc)
{
	uint32_t	reg;
	uint16_t	address;

	printf("Exec sti\n");
	(void)e;
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 0, 1);
		proc->carry = (!reg ? 1 : 0);
		address = src_param(proc, 0, 1, 1) + src_param(proc, 0, 2, 1);
		set_mem_uint32(proc, address % IDX_MOD, reg);
		printf("Exec sti ok\n");
	}
}

void	exec_fork(t_env *e, t_process *proc)
{
	uint16_t	address;

	printf("Exec fork\n");
	(void)e;
	if (valid_params(proc))
	{
		address = src_param(proc, 1, 0, 0);
		//A faire
		printf("Exec fork ok\n");
	}
}
