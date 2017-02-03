/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 16:24:51 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/03 17:31:04 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	die(t_env *e, char *error)
{
	//free FUNCTIONS
	(void)e;
	ft_printf("{:red}Error: %s{:eoc}\n", error);
	exit(-1);
}

void	free_env(t_env *e)
{
	uint32_t	i;

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
}
