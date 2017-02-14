/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:43:35 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/14 15:46:44 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t	ft_straight_bytes(unsigned int bytes)
{
	unsigned int	ret;

	ret = bytes & 0xFF;
	ret <<= 8;
	ret += bytes >> 8 & 0xFF;
	ret <<= 8;
	ret += bytes >> 16 & 0xFF;
	ret <<= 8;
	ret += bytes >> 24 & 0xFF;
	return (ret);
}

void		ft_straight_header(t_header *header, t_env *env)
{
	header->magic = ft_straight_bytes(header->magic);
	if (header->magic != COREWAR_EXEC_MAGIC)
		die(env, "magic is not 0xea83f3");
	header->prog_size = ft_straight_bytes(header->prog_size);
	if (header->prog_size > CHAMP_MAX_SIZE)
		die(env, "prog_size > CHAMP_MAX_SIZE");
}

int			valid_player(t_env *e, uint32_t id)
{
	uint32_t	i;

	i = -1;
	while (++i < e->nb_player)
		if (e->player_id[i] == id)
			return (i);
	return (-1);
}

void		pc_moves(t_process *proc, int i)
{
	int		j;

	j = -1;
	ft_printf("\033[0mADV %d (0x%04x -> 0x%04x) ", i, proc->start + proc->pc,\
									(proc->start + proc->pc + i) % MEM_SIZE);
	while (++j < i)
	{
		ft_putnbr_hex(get_mem_uint8(proc, j), 2);
		ft_putchar(j + 1 < i ? ' ' : '\n');
	}
}

void		wait_enter(t_env *e)
{
	char	c;
	int		flags;

	ft_printf("Press enter to continue...");
	c = '\0';
	flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	while (c != '\n')
	{
		if (e->gui)
		{
			gui(e, &(e->sdl));
			if (!e->run)
				break ;
		}
		else if (e->fdf)
		{
			fdf(e, &(e->sdl));
			if (!e->run)
				break ;
		}
		read(0, &c, 1);
	}
	fcntl(0, F_SETFL, flags);
}
