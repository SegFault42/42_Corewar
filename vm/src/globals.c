/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:26:12 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 17:35:36 by qhonore          ###   ########.fr       */
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
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{"jmp", 1, {T_DIR}, 17, 25, "jump", 0, 1},
	{"cmp", 2, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR},\
		18, 3, "cmp (val1 == val2)", 1, 0},
	{"div", 3, {T_REG, T_REG, T_REG}, 19, 20, "division", 1, 0},
	{"mul", 3, {T_REG, T_REG, T_REG}, 20, 20, "multiplication", 1, 0}
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
	exec_aff,
	exec_jmp,
	exec_cmp,
	exec_div,
	exec_mul
};

t_env		*get_env(void)
{
	static t_env env;

	return (&env);
}

t_op		get_op(int i)
{
	return (g_op_tab[i - 1]);
}

static void	next_instruction(t_env *e, t_process *proc)
{
	t_instruction	*inst;

	inst = &(proc->inst);
	if (inst->opcode != ZJMP && inst->opcode != JMP)
	{
		if (e->verbose & SHOW_PC_MOVES)
			pc_moves(proc, inst->i + 1);
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = 0;
		proc->pc = (proc->pc + inst->i + 1) % MEM_SIZE;
		g_pc[(proc->start + proc->pc) % MEM_SIZE] = proc->player_id;
	}
	init_instruction(inst);
}

static void	color_inst(t_env *e, t_process *proc)
{
	if (e->nb_player > 0 && proc->player_id == e->player_id[0])
		ft_putstr("\033[38;5;29m");
	else if (e->nb_player > 1 && proc->player_id == e->player_id[1])
		ft_putstr("\033[38;5;55m");
	else if (e->nb_player > 2 && proc->player_id == e->player_id[2])
		ft_putstr("\033[38;5;88m");
	else if (e->nb_player > 3 && proc->player_id == e->player_id[3])
		ft_putstr("\033[38;5;208m");
}

void		exec_instruction(t_env *e, t_process *proc)
{
	int		opcode;

	if (proc->inst.bad_ocp)
		next_instruction(e, proc);
	else
	{
		color_inst(e, proc);
		get_values(proc, &(proc->inst));
		opcode = proc->inst.opcode;
		g_exec_op[proc->inst.opcode - 1](e, proc);
		ft_putstr("\033[0m");
		if (opcode != FORK && opcode != LFORK)
			next_instruction(e, proc);
	}
	if (e->op_pause)
		wait_enter(e);
}
