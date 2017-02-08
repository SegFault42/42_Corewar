/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:18:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/08 14:46:44 by qhonore          ###   ########.fr       */
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
					p->pc = (p->pc + 1) % MEM_SIZE;
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
				ft_printf("Process %d is {:red}dead{:eoc}\n", i);
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

static int	dump_n_wait(t_env *e)
{
	char	c;
	int		flags;

	dump_memory(e);
	ft_printf("Press enter to continue...");
	c = '\0';
	flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	while (c != '\n')
	{
		if (e->gui && !gui(e, &(e->sdl)))
		{
			fcntl(0, F_SETFL, flags);
			return (0);
		}
		read(0, &c, 1);
	}
	fcntl(0, F_SETFL, flags);
	return (1);
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
		if (e->gui && !gui(e, sdl))
			break ;
		if (e->dump && e->cycle == e->dump)
			break ;
		if (e->sdump && !(e->cycle % e->sdump) && !dump_n_wait(e))
			 break ;
	}
}
