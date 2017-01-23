/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:40:39 by framel            #+#    #+#             */
/*   Updated: 2017/01/23 16:37:35 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint32_t	ft_set_start(uint32_t i, uint32_t nb_usr)
{
	uint32_t ret;

	ret = (MEM_SIZE / nb_usr) * i;
	return (ret);
}

int	ft_memload(uint8_t mem[MEM_SIZE], t_env *env)
{
	uint32_t i;
	uint32_t j;
	uint32_t start;

	i = 0;
	while (i < env->nb_usr)
	{
		j = 0;
		start = ft_set_start(i, env->nb_usr);
		while(j < env->header[i].prog_size)
		{
			mem[start + j] = env->process[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_run(uint8_t mem[MEM_SIZE], t_env *env)
{
	uint32_t	i;

	i = 0;
	ft_memload(mem, env);
	/////TEST//////////
	while (i < MEM_SIZE)
	{
		printf("%02X ", mem[i++]);
		if (!(i % 32))
			printf("\n");
	}
	/////////////////////
	return (0);
}
