/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/10 12:17:38 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	announce_winner(t_env *e)
{
	int		id;

	if (!e->alives || e->cycle_die <= 0)
	{
		id = valid_player(e, e->last_live);
		if (e->last_live)
			ft_printf("Player %d(%s) as {:green}won{:eoc}.\n", e->last_live,\
												e->player[id].header.prog_name);
		else
			ft_printf("No live, it's a {:yellow}draw{:eoc}.\n");
	}
}

static void	usage(void)
{
	ft_printf("{:yellow}Usage: ./corewar [-dvsgfp] [-n id] champ1.cor [-n id] \
champ2.cor\n");
	ft_printf("-g   : SDL output mode\n");
	ft_printf("-f   : FDF output mode\n");
	ft_printf("-p   : Pauses after each instruction\n");
	ft_printf("-d N : Dumps memory after N cycles then exits\n");
	ft_printf("-s N : Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("-v N : Verbosity levels, can be added together to enable several\
\n\t- 0 : Show only essentials\n\t- 1 : Show lives\n\t- 2 : Show cycles\n\t- 4 \
: Show operations (Params are NOT litteral ...)\n\t- 8 : Show deaths\n\t- 16 : \
Show PC movements{:eoc}\n");
	exit(-1);
}

int			main(int argc, char **argv)
{
	t_env	*e;

	if (argc < 2)
		usage();
	e = get_env();
	init_env(e);
	init_memory();
	init_vm(e, argc, argv);
	if (e->gui)
		init_sdl(&(e->sdl));
	run(e, &(e->sdl));
	if (e->dump || e->sdump)
		dump_memory(e);
	announce_winner(e);
	free_env(e);
}
