/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/18 01:40:01 by qhonore          ###   ########.fr       */
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
		if (get_op(opcode).carry)
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
	proc.reg[0] = 0xffffffff;
	while (ac--)
		g_mem[ac - 1] = strtol(av[ac], NULL, 16);
	if (!check_opcode(&proc, get_mem_uint8(&proc, proc.inst.i)))
		printf("Bad opcode\n");
	if (!check_ocp(&proc, get_mem_uint8(&proc, proc.inst.i)))
		printf("Bad ocp\n");
	exec_instruction(&proc);
	printf("Instruction:\nopcode = %02X\nocp = %02X\nparam[0] = %d, %02X\nparam[1] = %d, %02X\nparam[2] = %d, %02X\n", proc.inst.opcode, proc.inst.ocp, proc.inst.param[0], proc.inst.val[0], proc.inst.param[1], proc.inst.val[1], proc.inst.param[2], proc.inst.val[2]);
	// set_mem_uint16(&proc, 0x40, 0xff10);
	// set_mem_uint32(&proc, 4096, 0xddaaff10);
	dump_memory(&proc);
}

// 0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01 00 00 00 01 09 ff fb
//sti 68(REG|DIR|DIR) -> 0b 68 01 00 0f 00 01
//ld D0(IND|REG) 90(D4|REG) -> 02 D0 00 10 05
//st 70(REG|IND) 50(REG|REG) -> 03 70 01 00 23
