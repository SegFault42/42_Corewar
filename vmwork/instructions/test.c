/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:14:47 by quentin           #+#    #+#             */
/*   Updated: 2017/01/13 20:06:25 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	set_param_type(uint8_t *param, int inf, int sup)
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

void	check_ocp(t_instruction *inst)
{
	inst->param1 = (inst->ocp & 64) + (inst->ocp & 128);
	set_param_type(&(inst->param1), 64, 128);
	inst->param2 = (inst->ocp & 16) + (inst->ocp & 32);
	set_param_type(&(inst->param2), 16, 32);
	inst->param3 = (inst->ocp & 4) + (inst->ocp & 8);
	set_param_type(&(inst->param3), 4, 8);
}

int		main(int ac, char **av)
{
	t_instruction	inst;

	inst.opcode = strtol(av[1], NULL, 16);
	inst.ocp = strtol(&(av[1][3]), NULL, 16);
	check_ocp(&inst);
	printf("Instruction:\nopcode = %d\nocp = %d\nparam1 = %d\nparam2 = %d\nparam3 = %d\n",\
	inst.opcode, inst.ocp, inst.param1, inst.param2, inst.param3);
	return (0);
}
