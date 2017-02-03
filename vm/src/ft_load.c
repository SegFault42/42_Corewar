/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:48:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/03 15:28:32 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/// 4 malloc have to be free including 1 in a loop ...

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

void		ft_straight_header(t_header *header)
{
	header->magic = ft_straight_bytes(header->magic);
	header->prog_size = ft_straight_bytes(header->prog_size);
}

int			ft_load(uint8_t fd[MAX_PLAYERS], t_env *env)
{
	uint32_t	i;

	i = -1;
	if (!(env->player = (t_player*)malloc(sizeof(t_player) * env->nb_player)))
		return (-1);
	while (++i < env->nb_player)
	{
		if (read(fd[i], &env->player[i].header, sizeof(t_header)) != \
				sizeof(t_header))
			return (-1);
		ft_straight_header(&env->player[i].header);
		env->player[i].op = (uint8_t *)malloc(env->player[i].header.prog_size \
				* sizeof(uint8_t));
		if (env->player[i].op == NULL)
			return (-1);
		if (read(fd[i], env->player[i].op, env->player[i].header.prog_size) != \
			env->player[i].header.prog_size)
			return (-1);
		close(fd[i]);
	}
	return (0);
}

int			parse_options(t_env *e, int argc, char **argv, int i)
{
	if (!ft_strcmp(argv[i], "-v") && i + 1 < argc && ft_isdigitstr(argv[i + 1]))
		e->verbose = ft_atoi(argv[++i]);
	if ((!ft_strcmp(argv[i], "-dump") || !ft_strcmp(argv[i], "-d"))
	&& i + 1 < argc && ft_isdigitstr(argv[i + 1]))
		e->dump = ft_atoi(argv[++i]);
	i++;
	return (i);
}

int			ft_parse(t_env *e, int argc, char **argv, uint8_t fd[MAX_PLAYERS])
{
	uint8_t i;
	uint8_t n;

	i = 1;
	n = 0;
	while (i < argc)
	{
		if (*argv[i] == '-')
			i = parse_options(e, argc, argv, i);
		else if (i < argc && n < MAX_PLAYERS)
		{
			fd[n] = open(argv[i], O_RDONLY);
			if (fd[n] < 0)
				return (-n);
			n++;
			i++;
		}
	}
	return (n);
}
