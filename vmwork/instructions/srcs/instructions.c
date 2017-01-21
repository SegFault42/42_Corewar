/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:32:19 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/21 20:36:31 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

void	exec_live(t_env *e, t_process *proc)
{
	uint32_t	val;

	val = src_param(proc, 0, 0, 0);
	printf("LIVE VAL = %d\n", val);
	if (val >= 1 && val <= e->nb_player)
	{
		e->player[val - 1].live += 1;
		printf("Exec live for %08X\n", val);
	}
}

void	exec_ld(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec ld\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 1, 0, 0);
		reg = src_param(proc, 0, 1, 0);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec ld ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}

void	exec_st(t_env *e, t_process *proc)
{
	uint32_t		val;
	uint16_t		dest;
	t_instruction	*inst;

	printf("Exec st\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		val = src_param(proc, 0, 0, 1);
		dest = src_param(proc, 1, 1, 0);
		proc->carry = (!val ? 1 : 0);
		dst_param(proc, 1, dest, val);
	}
}

void	exec_add(t_env *e, t_process *proc)
{
	uint8_t			reg;
	uint32_t		val;
	t_instruction	*inst;

	printf("Exec add\n");
	(void)e;
	inst = &(proc->inst);
	if (valid_params(proc))
	{
		reg = src_param(proc, 0, 2, 0);
		val = src_param(proc, 0, 0, 1) + src_param(proc, 0, 1, 1);
		proc->carry = (!val ? 1 : 0);
		proc->reg[reg] = val;
		printf("Exec add ok: proc->reg[%d] = %08X\n", reg, proc->reg[reg]);
	}
}
