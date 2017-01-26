/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:43:35 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/26 17:07:05 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

bool		valid_reg(uint8_t reg)
{
	if (reg >= 0 && reg < REG_NUMBER)
		return (1);
	return (0);
}

bool		valid_params(t_process *proc)
{
	t_instruction	*inst;
	uint8_t			nb;

	inst = &(proc->inst);
	nb = get_op(inst->opcode).nb_arg;
	while (nb)
	{
		nb--;
		if (inst->param[nb] == T_REG && !valid_reg(inst->val[nb] - 1))
			return (0);
	}
	return (1);
}

/*
********************************************************************************
**                                 src_param()                                **
** idx: use IDX_MOD ? true | false                                            **
** i: index for inst->param[] (0 to 2)                                        **
** v_reg: true -> get reg value | false -> get reg index                      **
********************************************************************************
*/

uint32_t	src_param(t_process *proc, bool idx, uint8_t i, bool v_reg)
{
	t_instruction	*inst;
	uint32_t		val;

	inst = &(proc->inst);
	if (inst->param[i] == T_IND)
	{
		if (idx)
	 		val = get_mem_uint32(proc, inst->val[i] % IDX_MOD);
		else
			val = get_mem_uint32(proc, inst->val[i]);
	}
	else if (inst->param[i] == T_REG)
	{
		if (v_reg)
			val = proc->reg[inst->val[i] - 1];
		else
			val = inst->val[i] - 1;
	}
	else// if (inst->param[i] == T_DIR)
		val = inst->val[i];
	return (val);
}

void		copy_processes(t_env *e, t_process *cpy)
{
	uint32_t	i;
	int			j;
	t_process	*p;

	i = -1;
	while (++i < e->nb_process)
	{
		j = -1;
		p = &(cpy[i]);
		p->inst = e->process[i].inst;
		p->carry = e->process[i].carry;
		p->start = e->process[i].start;
		p->pc = e->process[i].pc;
		while (++j < REG_NUMBER)
			p->reg[j] = e->process[i].reg[j];
	}
	free(e->process);
	e->process = cpy;
}

void		fork_process(t_env *e, t_process *proc, uint16_t pc)
{
	t_process	*new;
	t_process	*cpy;
	int			i;

	if (!(cpy = (t_process*)malloc(sizeof(t_process) * (e->nb_process + 1))))
		printf("fork: malloc failure\n");
	copy_processes(e, cpy);
	new = &(e->process[e->nb_process]);
	proc = &(e->process[e->cur_process]);
	e->nb_process += 1;
	init_instruction(&(new->inst));
	new->player_id = proc->player_id;
	new->carry = proc->carry;
	new->start = proc->start;
	new->pc = pc % MEM_SIZE;
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = proc->reg[i];
	printf("FORK, process%d\n", e->nb_process);
	printf("carry: %d, start: %04X, pc = %04X\n", new->carry, new->start, new->pc);
	printf("reg(1:%08X, 2:%08X, 3:%08X, 4:%08X, 5:%08X, 6:%08X, 7:%08X, 8:%08X", new->reg[0], new->reg[1], new->reg[2], new->reg[3], new->reg[4], new->reg[5], new->reg[6], new->reg[7]);
	printf(", 9:%08X, 10:%08X, 11:%08X, 12:%08X, 13:%08X, 14:%08X, 15:%08X, 16:%08X)\n", new->reg[8], new->reg[9], new->reg[10], new->reg[11], new->reg[12], new->reg[13], new->reg[14], new->reg[15]);
}
