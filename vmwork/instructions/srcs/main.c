/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/24 11:51:24 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"

#define OP_SIZE 31

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

void		check_players_inst(t_env *e)
{
	t_process	*p;

	e->cur_process = e->nb_process;
	while (--(e->cur_process) >= 0)
	{
		p = &(e->process[e->cur_process]);
		if (p->inst.n_cycle == -1)
		{
			if (!check_opcode(p, get_mem_uint8(p, p->inst.i))
			|| !check_ocp(p, get_mem_uint8(p, p->inst.i)))
				p->pc++;
			dump_memory(e);
		}
		else
		{
			if (!(p->inst.n_cycle))
			{
				printf("EXEC_INSTRUCTION FOR PROC%d\n", e->cur_process + 1);
				exec_instruction(e, p);
			}
			else
				(p->inst.n_cycle)--;
		}
	}
}

static void	run(t_env *e)
{
	e->run = 1;
	while (e->run)
	{
		check_players_inst(e);
	}
}

void	init_players(t_env *e)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < e->nb_player)
	{
		e->player[i].live = 0;
		j = -1;
		while (++j < OP_SIZE)//Remplacer OP_SIZE -> Nombre de uint8_t
		{
			g_mem[e->process[i].start + j] = e->player[i].op[j];
			g_color[e->process[i].start + j] = i + 1;
		}
	}
}

static void	init_vm(t_env *e)
{
	//TEMPORAIRE////////////////////////////////////////////////////////////////
	uint32_t	i = -1;
	// 0B 68 01 00 12 00 01 06 64 01 00 00 00 00 02 0C 00 08 01 00 00 00 02 01 00 00 00 08 09 FF F6
	uint8_t		ops[OP_SIZE] = {0x0b, 0x68, 0x01, 0x00, 0x12, 0x00, 0x01, 0x06, 0x64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0c, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x08, 0x09, 0xff, 0xf6};
	e->nb_player = 3;
	e->nb_process = e->nb_player;
	if ((e->player = (t_player*)malloc(sizeof(t_player) * e->nb_player)))
	{
		while (++i < e->nb_player)
		{
			if ((e->player[i].op = malloc(sizeof(uint8_t) * OP_SIZE)))
			{
				int j = -1;
				while (++j < OP_SIZE)
					e->player[i].op[j] = ops[j];
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
	if ((e->process = (t_process*)malloc(sizeof(t_process) * e->nb_process)))
		init_processes(e);
	init_players(e);
}

int		main(void)
{
	t_env		e;

	init_env(&e);
	init_memory();
	//Lecteur
	init_vm(&e);
	run(&e);
}

// 0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01 00 00 00 01 09 ff fb
//sti 68(REG|DIR|DIR) -> 0b 68 01 00 0f 00 01
//ld D0(IND|REG) 90(D4|REG) -> 02 D0 00 10 05
//st 70(REG|IND) 50(REG|REG) -> 03 70 01 00 23
//add 54(REG|REG|REG) -> 04 54 01 02 03
//sub 54(REG|REG|REG) -> 05 54 01 02 03
//and A4(D4|D4|REG) -> 06 A4 FF FF FF FF 00 FF 00 0F 05
//or A4(D4|D4|REG) -> 07 A4 FF FF FF FF 00 FF 00 0F 05
//xor A4(D4|D4|REG) -> 08 A4 FF FF FF FF 00 FF 00 0F 05

// ./corewar -v 4 test2.cor -> Returned values
