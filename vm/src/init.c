/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/21 14:59:45 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_memory(void)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
		g_mem[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
		g_color[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
		g_pc[i] = 0;
}

void		init_instruction(t_instruction *inst)
{
	inst->opcode = 0;
	inst->ocp = 0;
	inst->param[0] = 0;
	inst->param[1] = 0;
	inst->param[2] = 0;
	inst->val[0] = 0;
	inst->val[1] = 0;
	inst->val[2] = 0;
	inst->n_cycle = -1;
	inst->bad_ocp = 0;
	inst->i = 0;
}

static void	init_process(t_process *process, uint32_t id, uint16_t start)
{
	int		i;

	i = 0;
	init_instruction(&(process->inst));
	process->carry = 0;
	process->start = start;
	process->pc = 0;
	process->player_id = id;
	process->live = 0;
	process->reg[0] = id;
	while (++i < REG_NUMBER)
		process->reg[i] = 0;
	g_pc[start] = id;
}

void		init_processes(t_env *e)
{
	t_process	*p;
	int			i;

	i = e->nb_process;
	while (--i >= 0)
	{
		if (!(p = (t_process*)malloc(sizeof(t_process))))
			die(e, "(t_process*)malloc(sizeof(t_process))");
		if (!(ft_lstadd(&(e->process), ft_lstnew_n(p, 0))))
			die(e, "ft_lstadd(&(e->process), ft_lstnew_n(p, NULL))");
		init_process(p, e->player_id[i], i * MEM_SIZE / e->nb_process);
		p->id = i + 1;
	}
}

void		init_env(t_env *e)
{
	int		i;

	e->run = 0;
	e->nb_player = 0;
	e->nb_process = 0;
	e->cur_process = 0;
	e->cycle = 0;
	e->cycle_die = CYCLE_TO_DIE;
	e->cur_die = 0;
	e->check = 0;
	e->alives = 0;
	e->lives = 0;
	e->valid_lives = 0;
	e->last_live = 0;
	e->player = NULL;
	e->process = NULL;
	e->verbose = 0;
	e->dump = 0;
	e->sdump = 0;
	e->fdf = 0;
	e->gui = 0;
	e->op_pause = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		e->player_id[i] = 0;
}
