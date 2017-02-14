/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/14 21:07:10 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	sdl_winner(t_env *e, char *winner)
{
	char	*win;
	char	*tmp;

	if (!(tmp = ft_itoa(e->last_live)))
		die(e, "Memory allocation failure ! ft_itoa(e->last_live)");
	if (!(win = ft_strjoin("Player ", tmp)))
		die(e, "Memory allocation failure ! ft_strjoin(\"Player \", tmp)");
	ft_strdel(&tmp);
	tmp = win;
	if (!(win = ft_strjoin(win, " (")))
		die(e, "Memory allocation failure ! ft_strjoin(win, \" (\")");
	ft_strdel(&tmp);
	tmp = win;
	if (!(win = ft_strjoin(win, winner)))
		die(e, "ft_strjoin(win, winner)");
	ft_strdel(&tmp);
	tmp = win;
	if (!(win = ft_strjoin(win, ") as won.")))
		die(e, "Memory allocation failure ! ft_strjoin(win, \") as won.\")");
	ft_strdel(&tmp);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	"Corewar", win, e->sdl.win.win);
	ft_strdel(&win);
}

static void	announce_winner(t_env *e)
{
	int		id;


	if (!e->alives || e->cycle_die <= 0)
	{
		id = valid_player(e, e->last_live);
		if (e->last_live)
		{
			ft_printf("Player %d(%s) as {:green}won{:eoc}.\n", e->last_live,\
												e->player[id].header.prog_name);
			sdl_winner(e, e->player[id].header.prog_name);
		}
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
	if (e->gui || e->fdf)
		init_sdl_gui(&(e->sdl));
	/*if (e->fdf)*/
		/*init_sdl_fdf(&(e->sdl));*/
	run(e, &(e->sdl));
	if (e->dump || e->sdump)
		dump_memory(e);
	announce_winner(e);
	free_env(e);
}
