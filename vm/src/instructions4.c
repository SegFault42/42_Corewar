/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 20:09:15 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_lld(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 0);
		reg = src_param(proc, 0, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | lld: %d -> r%d\n",\
											e->cur_process + 1, val, reg + 1);
	}
}

void	exec_lldi(t_env *e, t_process *proc)
{
	uint8_t			reg;
	int32_t			src1;
	int32_t			src2;
	int32_t			address;
	uint32_t		val;

	if (valid_params(proc))
	{
		src1 = src_param(proc, 1, 0, 1);
		if (proc->inst.param[0] == T_DIR)
			src1 = get_address(src1);
		src2 = get_address(src_param(proc, 1, 1, 1));
		address = src1 + src2;
		val = get_mem_uint32(proc, address);
		reg = src_param(proc, 0, 2, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | lldi: %d -> r%d\n | load from %d(PC: %d)\n",\
			e->cur_process + 1, val, reg + 1, src1 + src2, proc->pc + address);
	}
}

void	exec_lfork(t_env *e, t_process *proc)
{
	int16_t			pc;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		pc = (proc->pc + mem_address(inst->val[0])) % MEM_SIZE;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | lfork: %d (%d)\n", e->cur_process + 1,\
												get_address(inst->val[0]), pc);
		if (e->verbose & SHOW_PC_MOVES)
			pc_moves(proc, 3);
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = 0;
		proc->pc = (proc->pc + 3) % MEM_SIZE;
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = proc->player_id;
		init_instruction(&(proc->inst));
		fork_process(e, proc, pc);
	}
}

void	exec_aff(t_env *e, t_process *proc)
{
	uint32_t	val;

	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 1);
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | aff: %d -> %C\n", e->cur_process + 1, val, val);
	}
}
