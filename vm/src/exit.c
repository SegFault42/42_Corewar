/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 16:24:51 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/14 19:58:45 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	free_env(t_env *e)
{
	uint32_t	i;
	t_win		*win;

	i = -1;
	if (e->player)
	{
		while (++i < e->nb_player)
			if (e->player[i].op)
				free(e->player[i].op);
		free(e->player);
	}
	if (e->process)
		free(e->process);
	if (e->gui || e->fdf)
	{
		TTF_Quit();
		win = &(e->sdl.win);
		close_window(win, EXIT_SUCCESS);
	}
}

void	die(t_env *e, char *error)
{
	free_env(e);
	ft_printf("{:red}Error: %s{:eoc}\n", error);
	exit(-1);
}
