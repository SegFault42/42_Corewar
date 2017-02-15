/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 20:09:05 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_zjmp(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc) && proc->carry)
	{
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = 0;
		proc->pc = (proc->pc + idx_address(inst->val[0])) % MEM_SIZE;
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = proc->player_id;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | zjmp: %d(%d) OK (PC: %d)\n", e->cur_process + 1,\
							inst->val[0], idx_address(inst->val[0]), proc->pc);
	}
	else
	{
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | zjmp: %d(%d) FAIL (PC: %d)\n", e->cur_process + 1,\
			inst->val[0], idx_address(inst->val[0]), (proc->pc + 3) % MEM_SIZE);
		if (e->verbose & SHOW_PC_MOVES)
			pc_moves(proc, 3);
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = 0;
		proc->pc = (proc->pc + 3) % MEM_SIZE;
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = proc->player_id;
	}
}

void	exec_ldi(t_env *e, t_process *proc)
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
		address = (src1 + src2) % IDX_MOD;
		val = get_mem_uint32(proc, address);
		reg = src_param(proc, 0, 2, 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | ldi: %d -> r%d\n | load from %d(PC+IDX: %d)\n",\
			e->cur_process + 1, val, reg + 1, src1 + src2, proc->pc + address);
	}
}

void	exec_sti(t_env *e, t_process *proc)
{
	uint32_t	reg;
	int32_t		src1;
	int32_t		src2;
	int32_t		address;

	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 0, 1);
		src1 = src_param(proc, 1, 1, 1);
		if (proc->inst.param[0] != T_IND)
			src1 = get_address(src1);
		src2 = get_address(src_param(proc, 1, 2, 1));
		address = (src1 + src2) % IDX_MOD;
		set_mem_uint32(proc, address, reg);
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | sti: r%d(%d) -> %d\n | store to %d(PC+IDX: %d)\n"\
			, e->cur_process + 1, src_param(proc, 0, 0, 0) + 1, reg, address,\
											src1 + src2, proc->pc + address);
	}
}

void	exec_fork(t_env *e, t_process *proc)
{
	int16_t			pc;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		pc = (proc->pc + idx_address(inst->val[0])) % MEM_SIZE;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | fork: %d(%d)\n", e->cur_process + 1,\
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
