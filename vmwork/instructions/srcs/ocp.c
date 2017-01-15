/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:46:17 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/15 17:52:36 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

static void	set_param_type(uint8_t *param, int inf, int sup)
{
	if (*param == inf)
		*param = REG_CODE;
	else if (*param == sup)
		*param = DIR_CODE;
	else if (*param == inf + sup)
		*param = IND_CODE;
	else
		*param = 0;
}

static void	get_params(t_instruction *inst, uint8_t ocp)
{
	inst->param1 = (ocp & 64) + (ocp & 128);
	set_param_type(&(inst->param1), 64, 128);
	inst->param2 = (ocp & 16) + (ocp & 32);
	set_param_type(&(inst->param2), 16, 32);
	inst->param3 = (ocp & 4) + (ocp & 8);
	set_param_type(&(inst->param3), 4, 8);
}

int			check_ocp(t_process *proc, uint8_t ocp)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (!inst->i)
		return (1);
	get_params(inst, g_mem[1]);
	if (g_mem[1])
	{
		inst->ocp = ocp;
		return (1);
	}
	return (0);
}
