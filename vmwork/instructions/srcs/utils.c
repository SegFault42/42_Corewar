/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:43:35 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/23 22:48:59 by qhonore          ###   ########.fr       */
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

void		dst_param(t_process *proc, uint8_t i, uint32_t dest, uint32_t val)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (inst->param[i] == T_IND)
	{
		set_mem_uint32(proc, dest, val);
		printf("Exec ok\n");
	}
	else if (inst->param[i] == T_REG)
	{
		proc->reg[dest] = val;
		printf("Exec ok: proc->reg[%d] = %08X\n", dest, val);
	}
}

void		fork_process(t_env *e, t_process *proc, uint16_t pc)
{
	t_process	*p;

	if (!(e->process = realloc(e->process, sizeof(t_process) * (e->nb_process + 1))))
		printf("realloc failure\n");
	p = &(e->process[e->nb_process]);
	ft_memcpy(p, proc, sizeof(t_process));
	p->pc = pc % MEM_SIZE;
	init_instruction(&(p->inst));
	e->nb_process += 1;
	printf("FORK, process%d\n", e->nb_process);
	printf("carry: %d, start: %04X, pc = %04X\n", p->carry, p->start, p->pc);
	printf("reg(1:%08X, 2:%08X, 3:%08X, 4:%08X, 5:%08X, 6:%08X, 7:%08X, 8:%08X", p->reg[0], p->reg[1], p->reg[2], p->reg[3], p->reg[4], p->reg[5], p->reg[6], p->reg[7]);
	printf(", 9:%08X, 10:%08X, 11:%08X, 12:%08X, 13:%08X, 14:%08X, 15:%08X, 16:%08X)\n", p->reg[8], p->reg[9], p->reg[10], p->reg[11], p->reg[12], p->reg[13], p->reg[14], p->reg[15]);
	p->reg[0] = 18;
	// sleep(5);
}
