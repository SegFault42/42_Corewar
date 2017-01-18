/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/17 23:35:41 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	init_memory(void)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
		g_mem[i] = 0x20;
}

void	init_instruction(t_instruction *inst)
{
	inst->opcode = 0;
	inst->ocp = 0;
	inst->param[0] = 0;
	inst->param[1] = 0;
	inst->param[2] = 0;
	inst->val[0] = 0;
	inst->val[1] = 0;
	inst->val[2] = 0;
	inst->n_cycle = 0;
	inst->i = 0;
}

void	init_process(t_process *process)
{
	int		i;

	i = -1;
	init_instruction(&(process->inst));
	process->carry = 0;
	process->start = 0;
	process->pc = 0;
	while (++i < REG_NUMBER)
		process->reg[i] = 0;
}
