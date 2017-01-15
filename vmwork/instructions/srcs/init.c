/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/15 17:45:10 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	init_memory(void)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
		g_mem[i] = 0;
}

void	init_instruction(t_instruction *inst)
{
	inst->opcode = 0;
	inst->ocp = 0;
	inst->param1 = 0;
	inst->param2 = 0;
	inst->param3 = 0;
	inst->val1 = 0;
	inst->val2 = 0;
	inst->val3 = 0;
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
