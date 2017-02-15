/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 20:08:40 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_live(t_env *e, t_process *proc)
{
	uint32_t	val;
	int			id;

	val = src_param(proc, 0, 0, 0);
	if (e->verbose & SHOW_OPERATIONS)
		ft_printf("P%d | live: %d\n", e->cur_process + 1, val);
	proc->live++;
	e->lives++;
	id = valid_player(e, val);
	if (id != -1)
	{
		e->player[id].live += 1;
		e->last_live = val;
		e->valid_lives++;
		if (e->verbose & SHOW_LIVE)
			ft_printf("\033[0mPlayer %d (%s) is {:green}alive{:eoc}\n", val,\
										e->player[id].header.prog_name);
	}
}

void	exec_ld(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 0);
		reg = src_param(proc, 0, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | ld: %d -> r%d\n",\
											e->cur_process + 1, val, reg + 1);
	}
}

void	exec_st(t_env *e, t_process *proc)
{
	uint32_t		val;
	uint16_t		dest;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 1);
		dest = src_param(proc, 1, 1, 0);
		if (inst->param[1] == T_IND)
		{
			set_mem_uint32(proc, idx_address(inst->val[1]), val);
			if (e->verbose & SHOW_OPERATIONS)
				ft_printf("P%d | st: r%d(%d) -> %d\n", e->cur_process + 1,\
								inst->val[0], val, idx_address(inst->val[1]));
		}
		else if (inst->param[1] == T_REG)
		{
			proc->reg[dest] = val;
			if (e->verbose & SHOW_OPERATIONS)
				ft_printf("P%d | st: r%d(%d) -> r%d\n", e->cur_process + 1,\
									inst->val[0], val, dest + 1);
		}
	}
}

void	exec_add(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		if (e->verbose & SHOW_OPERATIONS)
			ft_printf("P%d | add: r%d + r%d = (%d) -> r%d\n",\
				e->cur_process + 1, inst->val[0], inst->val[1], val, reg + 1);
	}
}
