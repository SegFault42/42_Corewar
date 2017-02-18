/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:18:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/16 14:03:37 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_players_inst(t_env *e)
{
	t_process	*p;

	e->cur_process = e->nb_process;
	while (--(e->cur_process) >= 0)
	{
		p = &(e->process[e->cur_process]);
		if (p->alive)
		{
			if (p->inst.n_cycle == -1)
			{
				if (!check_opcode(p, get_mem_uint8(p, p->inst.i)))
				{
					g_pc[(p->start + p->pc) % MEM_SIZE] = 0;
					p->pc = (p->pc + 1) % MEM_SIZE;
					g_pc[(p->start + p->pc) % MEM_SIZE] = p->player_id;
				}
				else if (!check_ocp(p, get_mem_uint8(p, p->inst.i)))
					p->inst.bad_ocp = 1;
			}
			if (!(p->inst.n_cycle))
				exec_instruction(e, p);
			else if (p->inst.n_cycle > 0)
				(p->inst.n_cycle)--;
		}
	}
}

static void	check_process(t_env *e, t_process *p, int i)
{
	if (p->alive)
	{
		if (!(p->live))
		{
			if (e->verbose & SHOW_DEATHS)
				ft_fprintf(2, RED"Process %d is \033[31mdead\033[0m\n", i);
			p->alive = 0;
		}
		else
			e->alives++;
		p->live = 0;
	}
}

static void	time_to_die(t_env *e)
{
	uint32_t	i;

	e->cur_die = 0;
	i = -1;
	e->alives = 0;
	e->check++;
	while (++i < e->nb_process)
		check_process(e, &(e->process[i]), i + 1);
	if (e->lives >= NBR_LIVE || e->check == MAX_CHECKS)
	{
		e->cycle_die -= CYCLE_DELTA;
		e->check = 0;
		if (e->verbose & SHOW_CYCLES)
			ft_printf("New cycle to die: %d\n", e->cycle_die);
	}
	i = -1;
	while (++i < e->nb_player)
		e->player[i].live = 0;
	e->lives = 0;
	e->valid_lives = 0;
	if (!e->alives || e->cycle_die <= 0)
		e->run = 0;
}

void		run(t_env *e, t_sdl *sdl)
{
	e->run = 1;
	while (e->run)
	{
		e->cycle++;
		e->cur_die++;
		if (e->verbose & SHOW_CYCLES)
			ft_printf("Current cycle: %d (%d / %d)\n", e->cycle,\
													e->cur_die, e->cycle_die);
		check_players_inst(e);
		if (e->cur_die == e->cycle_die)
			time_to_die(e);
		if (e->gui)
			gui(e, sdl);
		else if (e->fdf)
			fdf(e, sdl);
		if (e->dump && e->cycle == e->dump)
			break ;
		if (e->sdump && !(e->cycle % e->sdump))
		{
			dump_memory(e);
			wait_enter(e);
		}
		SDL_Delay(e->sdl.win.delay);
	}
}
