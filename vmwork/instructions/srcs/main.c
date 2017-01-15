/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/15 20:30:49 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

int		check_opcode(t_process *proc, uint8_t opcode)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (opcode >= 1 && opcode <= OPS_NUMBER)
	{
		inst->opcode = opcode;
		if (get_op(opcode).ocp)
			(inst->i)++;
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_process		proc;

	if (ac < 3)
	{
		printf("Usage: ./corewar [opcode] [ocp] (param1) ...\n");
		return (-1);
	}
	init_memory();
	init_process(&proc);
	while (ac--)
		g_mem[ac - 1] = strtol(av[ac], NULL, 16);
	if (!check_opcode(&proc, get_mem_uint8(&proc, proc.inst.i)))
		printf("Bad opcode\n");
	if (!check_ocp(&proc, get_mem_uint8(&proc, proc.inst.i)))
		printf("Bad ocp\n");
	printf("Instruction:\nopcode = %02X\nocp = %02X\nparam1 = %d\nparam2 = %d\nparam3 = %d\n", proc.inst.opcode, proc.inst.ocp, proc.inst.param1, proc.inst.param2, proc.inst.param3);
	// set_mem_uint16(&proc, 0x40, 0xff10);
	// set_mem_uint32(&proc, 0x80, 0xddaaff10);
	dump_memory(&proc);
}
