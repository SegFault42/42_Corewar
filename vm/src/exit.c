/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 16:24:51 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/17 13:26:36 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	free_processes(t_list *process)
{
	t_list	*tmp;

	while (process)
	{
		if (process->content)
			free(process->content);
		tmp = process->next;
		free(process);
		process = tmp;
	}
}

void		free_env(t_env *e)
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
	free_processes(e->process);
	if (e->gui || e->fdf)
	{
		TTF_Quit();
		win = &(e->sdl.win);
		close_window(win, EXIT_SUCCESS);
	}
}

void		die(t_env *e, char *error)
{
	free_env(e);
	ft_fprintf(2, RED"Error: %s\n"END, error);
	exit(-1);
}
