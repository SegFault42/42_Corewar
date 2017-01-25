/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/25 16:45:49 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	exec_lld(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec lld\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 0);
		reg = src_param(proc, 0, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec lld ok: proc->reg[%d] = %d\n", reg + 1, proc->reg[reg]);
	}
}

void	exec_lldi(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint16_t		address;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec lldi\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		address = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		val = get_mem_uint32(proc, address);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec lldi ok: proc->reg[%d] = %d\n", reg + 1, proc->reg[reg]);
	}
}

void	exec_lfork(t_env *e, t_process *proc)
{
	uint16_t	pc;

	printf("Exec lfork\n");
	if (valid_params(proc))
	{
		pc = proc->pc + src_param(proc, 0, 0, 0);
		proc->pc = (proc->pc + 3) % MEM_SIZE;
		init_instruction(&(proc->inst));
		fork_process(e, proc, pc);
		printf("Exec lfork ok\n");
	}
}

void	exec_aff(t_env *e, t_process *proc)
{
	uint32_t	val;

	printf("Exec aff\n");
	(void)e;
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 1);
		proc->carry = (!val ? 1 : 0);
		//A faire
		printf("Exec aff ok\n");
	}
}
