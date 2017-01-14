/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/14 15:56:59 by qhonore          ###   ########.fr       */
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

void	check_opcode(t_instruction *inst)
{
	if (inst->opcode >= 1 && inst->opcode <= OPS_NUMBER)
	{
		
	}
}

int		main(int ac, char **av)
{
	t_instruction	inst;

	if (ac < 3)
	{
		printf("Usage: ./corewar [opcode] [ocp]\n");
		return (-1);
	}
	init_memory();
	while (ac--)
		g_mem[ac - 1] = strtol(av[ac], NULL, 16);
	inst.opcode = g_mem[0];
	check_opcode(&inst);
	inst.ocp = g_mem[1];
	check_ocp(&inst);
	printf("Instruction:\nopcode = %02X\nocp = %02X\nparam1 = %d\nparam2 = %d\nparam3 = %d\n", inst.opcode, inst.ocp, inst.param1, inst.param2, inst.param3);
	dump_memory();
}
