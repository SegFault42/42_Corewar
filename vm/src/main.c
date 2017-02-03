/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/03 15:28:47 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	announce_winner(t_env *e)
{
	int		id;

	if (!e->alives || e->cycle_die <= 0)
	{
		id = e->last_live;
		if (e->last_live)
			ft_printf("Player %d(%s) as {:green}won{:eoc}.\n", id,\
											e->player[id - 1].header.prog_name);
		else
			ft_printf("No live, it's a {:yellow}draw{:eoc}.\n");
	}
}

int			main(int argc, char **argv)
{
	t_env	e;

	if (argc < 2)
		return (-1);
	init_env(&e);
	init_memory();
	if (!(init_vm(&e, argc, argv)))
		return (-1);//free
	run(&e);
	if (e.dump)
		dump_memory(&e);
	announce_winner(&e);
}
