/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:26:12 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/28 20:04:16 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[OPS_NUMBER] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},\
		6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},\
		11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};

t_func	g_exec_op[OPS_NUMBER] =
{
	exec_live,
	exec_ld,
	exec_st,
	exec_add,
	exec_sub,
	exec_and,
	exec_or,
	exec_xor,
	exec_zjmp,
	exec_ldi,
	exec_sti,
	exec_fork,
	exec_lld,
	exec_lldi,
	exec_lfork,
	exec_aff
};

t_op		get_op(int i)
{
	return (g_op_tab[i - 1]);
}

void		pc_moves(t_process *proc, int i)
{
	int		j;

	j = -1;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", i, proc->start + proc->pc,\
									(proc->start + proc->pc + i) % MEM_SIZE);
	while (++j < i)
	{
		ft_putnbr_hex(get_mem_uint8(proc, j), 2);
		ft_putchar(j + 1 < i ? ' ' : '\n');
	}
}

static void	next_instruction(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (inst->opcode != ZJMP)
	{
		if (e->verbose & SHOW_PC_MOVES)
			pc_moves(proc, inst->i + 1);
		proc->pc = (proc->pc + inst->i + 1) % MEM_SIZE;
	}
	init_instruction(inst);
}

void		exec_instruction(t_env *e, t_process *proc)
{
	int		opcode;

	if (proc->inst.bad_ocp)
	{
		if (e->verbose & SHOW_PC_MOVES)
		{
			ft_printf("BAD OCP: ");
			pc_moves(proc, 2);
		}
		proc->pc = (proc->pc + 2) % MEM_SIZE;
		init_instruction(&(proc->inst));
	}
	else
	{
		opcode = proc->inst.opcode;
		g_exec_op[proc->inst.opcode - 1](e, proc);
		if (opcode != FORK && opcode != LFORK)
			next_instruction(e, proc);
	}
	// dump_memory(e);
	// char* str; while (get_next_line(0, &str) != 1){free(str);}
}
