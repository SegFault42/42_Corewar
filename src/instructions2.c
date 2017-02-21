/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/27 20:45:53 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_sub(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) - src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | sub: r%d - r%d = (%d) -> r%d\n",\
				e->cur_process + 1, inst->val[0], inst->val[1], val, reg + 1);
	}
}

void	exec_and(t_env *e, t_process *proc)
{
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1) & src_param(proc, 1, 1, 1);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | and: %d & %d = (%d) -> r%d\n", e->cur_process + 1,\
			src_param(proc, 1, 0, 1), src_param(proc, 1, 1, 1), val, reg + 1);
	}
}

void	exec_or(t_env *e, t_process *proc)
{
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1) | src_param(proc, 1, 1, 1);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | or: %d | %d = (%d) -> r%d\n", e->cur_process + 1,\
			src_param(proc, 1, 0, 1), src_param(proc, 1, 1, 1), val, reg + 1);
	}
}

void	exec_xor(t_env *e, t_process *proc)
{
	uint32_t		val;
	uint8_t			reg;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 1) ^ src_param(proc, 1, 1, 1);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | xor: %d ^ %d = (%d) -> r%d\n", e->cur_process + 1,\
			src_param(proc, 1, 0, 1), src_param(proc, 1, 1, 1), val, reg + 1);
	}
}
