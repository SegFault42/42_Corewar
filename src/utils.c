/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:43:35 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/21 15:04:09 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

int			check_opcode(t_process *proc, uint8_t opcode)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (opcode >= 1 && opcode <= OPS_NUMBER)
	{
		inst->opcode = opcode;
		if (get_op(opcode).carry)
			(inst->i)++;
		return (1);
	}
	init_instruction(inst);
	return (0);
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
			val = get_mem_uint32(proc, idx_address(inst->val[i]));
		else
			val = get_mem_uint32(proc, mem_address(inst->val[i]));
	}
	else if (inst->param[i] == T_REG)
	{
		if (v_reg)
			val = proc->reg[inst->val[i] - 1];
		else
			val = inst->val[i] - 1;
	}
	else
		val = inst->val[i];
	return (val);
}

void		fork_process(t_env *e, t_process *proc, uint16_t pc)
{
	t_process	*new;
	int			i;

	if (!(new = (t_process*)malloc(sizeof(t_process))))
		die(e, "(t_process*)malloc(sizeof(t_process))");
	if (!(ft_lstadd(&(e->process), ft_lstnew_n(new, 0))))
		die(e, "ft_lstadd(&(e->process), ft_lstnew_n(p, NULL))");
	e->nb_process += 1;
	init_instruction(&(new->inst));
	new->id = e->nb_process;
	new->player_id = proc->player_id;
	new->live = proc->live;
	new->carry = proc->carry;
	new->start = proc->start;
	new->pc = pc % MEM_SIZE;
	g_pc[(new->start + new->pc) % MEM_SIZE] = new->player_id;
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = proc->reg[i];
	e->alives++;
}

void		check_instruction(t_env *e, t_process *p)
{
	if (p->inst.n_cycle == -1)
	{
		if (!check_opcode(p, get_mem_uint8(p, p->inst.i)))
		{
			g_pc[(p->start + p->pc) % MEM_SIZE] = 0;
			p->pc = (p->pc + 1) % MEM_SIZE;
			g_pc[(p->start + p->pc) % MEM_SIZE] = p->player_id;
		}
		else if (!check_ocp(p, get_mem_uint8(p, p->inst.i)))
			p->inst.bad_ocp = 1;
	}
	if (!(p->inst.n_cycle))
		exec_instruction(e, p);
	else if (p->inst.n_cycle > 0)
		(p->inst.n_cycle)--;
}
