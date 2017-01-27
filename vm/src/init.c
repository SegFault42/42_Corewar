/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:44:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/27 12:25:55 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_memory(void)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
		g_mem[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
		g_color[i] = 0;
}

void	init_instruction(t_instruction *inst)
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
	process->player_id = id - 1;
	process->reg[0] = id;
	while (++i < REG_NUMBER)
		process->reg[i] = 0;
}

void	init_processes(t_env *e)
{
	t_process	*p;
	uint32_t	i;

	i = -1;
	while (++i < e->nb_process)
	{
		p = &(e->process[i]);
		init_process(p, i + 1, i * MEM_SIZE / e->nb_process);
	}
}

void	init_env(t_env *e)
{
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
	e->player = 0;
	e->process = 0;
	e->verbose = 0;
}
