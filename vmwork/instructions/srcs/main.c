/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/14 21:54:30 by qhonore          ###   ########.fr       */
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

void	get_params(t_instruction *inst, uint8_t ocp)
{
	inst->param1 = (ocp & 64) + (ocp & 128);
	set_param_type(&(inst->param1), 64, 128);
	inst->param2 = (ocp & 16) + (ocp & 32);
	set_param_type(&(inst->param2), 16, 32);
	inst->param3 = (ocp & 4) + (ocp & 8);
	set_param_type(&(inst->param3), 4, 8);
}

int		check_opcode(t_instruction *inst, uint8_t opcode)
{
	if (opcode >= 1 && opcode <= OPS_NUMBER)
	{
		inst->opcode = opcode;
		if (get_op(opcode).ocp == 0)
		{ printf("NO OCP:\n");/* No OCP -> Don't move PC */}
		return (1);
	}
	return (0);
}

int		check_ocp(t_instruction *inst, uint8_t ocp)
{
	if (get_op(inst->opcode).ocp == 0)
		return (1);
	get_params(inst, g_mem[1]);
	if (g_mem[1])
	{
		inst->ocp = ocp;
		return (1);
	}
	return (0);
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
	if (!check_opcode(&inst, g_mem[0]))
		printf("Bad opcode\n");
	if (!check_ocp(&inst, g_mem[1]))
		printf("Bad ocp\n");
	printf("Instruction:\nopcode = %02X\nocp = %02X\nparam1 = %d\nparam2 = %d\nparam3 = %d\n", inst.opcode, inst.ocp, inst.param1, inst.param2, inst.param3);
	dump_memory();
}
