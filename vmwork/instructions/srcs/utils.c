/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:43:35 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/18 20:49:44 by qhonore          ###   ########.fr       */
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
********************************************
**               store_param              **
** idx: 1 -> IDX_MOD | 0 -> no IDX_MOD    **
** i: index for inst->param[]             **
** v_reg: 1 -> reg value | 0 -> reg index **
********************************************
*/

uint32_t	store_param(t_process *proc, bool idx, uint8_t i, bool v_reg)
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
