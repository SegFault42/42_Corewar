/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 20:09:30 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_jmp(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = 0;
		proc->pc = (proc->pc + idx_address(inst->val[0])) % MEM_SIZE;
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = proc->player_id;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | zjmp: %d(%d) OK (PC: %d)\n", e->cur_process + 1,\
							inst->val[0], idx_address(inst->val[0]), proc->pc);
	}
}

void	exec_cmp(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		if (src_param(proc, 1, 0, 1) == src_param(proc, 1, 1, 1))
			proc->carry = 1;
		else
			proc->carry = 0;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | cmp: %d == %d -> %d\n", e->cur_process + 1,\
			src_param(proc, 1, 0, 1), src_param(proc, 1, 1, 1), proc->carry);
	}
}

void	exec_div(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc) && src_param(proc, 0, 1, 1))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) / src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | div: r%d / r%d = (%d) -> r%d\n",\
				e->cur_process + 1, inst->val[0], inst->val[1], val, reg + 1);
	}
}

void	exec_mul(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) * src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | mul: r%d * r%d = (%d) -> r%d\n",\
				e->cur_process + 1, inst->val[0], inst->val[1], val, reg + 1);
	}
}
