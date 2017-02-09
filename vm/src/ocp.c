/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:46:17 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/02 12:28:37 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	set_param_type(uint8_t *param, int inf, int sup)
{
	if (*param == inf)
		*param = T_REG;
	else if (*param == sup)
		*param = T_DIR;
	else if (*param == inf + sup)
		*param = T_IND;
	else
		*param = 0;
}

static void	get_params(t_instruction *inst, uint8_t ocp)
{
	inst->param[0] = (ocp & 64) + (ocp & 128);
	set_param_type(&(inst->param[0]), 64, 128);
	inst->param[1] = (ocp & 16) + (ocp & 32);
	set_param_type(&(inst->param[1]), 16, 32);
	inst->param[2] = (ocp & 4) + (ocp & 8);
	set_param_type(&(inst->param[2]), 4, 8);
}

int			check_params(t_instruction *inst)
{
	t_op	op;
	int		i;

	op = get_op(inst->opcode);
	i = -1;
	while (++i < op.nb_arg)
		if (!(inst->param[i] & op.arg[i]))
			return (0);
	return (1);
}

void		get_values(t_process *proc, t_instruction *inst)
{
	t_op	op;
	int		i;

	op = get_op(inst->opcode);
	i = -1;
	while (++i < op.nb_arg)
	{
		if ((inst->param[i] == T_DIR && op.direct) || inst->param[i] == T_IND)
		{
			inst->val[i] = get_mem_uint16(proc, ++(inst->i));
			inst->i += 1;
		}
		else if (inst->param[i] == T_DIR && !op.direct)
		{
			inst->val[i] = get_mem_uint32(proc, ++(inst->i));
			inst->i += 3;
		}
		else
			inst->val[i] = get_mem_uint8(proc, ++(inst->i));
	}
}

int			check_ocp(t_process *proc, uint8_t ocp)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (!(get_op(inst->opcode).carry))
		inst->param[0] = T_DIR;
	else
	{
		get_params(inst, ocp);
		inst->ocp = ocp;
	}
	inst->n_cycle = get_op(inst->opcode).n_cycle - 1;
	if (check_params(inst))
		return (1);
	get_values(proc, inst);
	return (0);
}
