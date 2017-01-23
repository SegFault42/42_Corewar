/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:27:14 by framel            #+#    #+#             */
/*   Updated: 2017/01/23 16:23:07 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/// 4 malloc have to be free including 1 in a loop ...

unsigned int ft_straight_bytes(unsigned int bytes)
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

void	ft_straight_header(header_t *header)
{
	header->magic = ft_straight_bytes(header->magic);
	header->prog_size = ft_straight_bytes(header->prog_size);
}

int	ft_load(uint8_t fd[MAX_PLAYERS], t_env *env)
{
	uint32_t	i;

	i = 0;
	env->header = (header_t *)malloc(env->nb_usr * sizeof(header_t));
	env->process = (uint8_t **)malloc(env->nb_usr * sizeof(uint8_t *));
	if (env->header == NULL || env->process == NULL)
		return (-1);
	while (i < env->nb_usr)
	{
		if (read(fd[i], &env->header[i], sizeof(header_t)) != sizeof(header_t))
				return (-1);
		ft_straight_header(&env->header[i]);
		env->process[i] = (uint8_t *)malloc(env->header[i].prog_size * \
			   	sizeof(uint8_t));
		if (env->process[i] == NULL)
			return (-1);
		if (read(fd[i], env->process[i], env->header[i].prog_size) != \
			   	env->header[i].prog_size)
				return (-1);
		close(fd[i]);
		i++;
	}
	return (0);
}

int ft_parse(int argc, char **argv, uint8_t fd[MAX_PLAYERS])
{
	uint8_t i;
	uint8_t n;

	i = 1;
	n = 0;
	while (i < argc && n < MAX_PLAYERS)
	{
		while (*argv[i] == '-')
			i++;
		if (i < argc)
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

int ft_run(uint8_t *, t_env *);

int	main(int argc, char **argv)
{
	t_env	*env;
	uint8_t	fd[MAX_PLAYERS];
	uint8_t mem[MEM_SIZE] = "weferget";

	if (argc < 2)
		return (-1);
	env = (t_env *)ft_memalloc(sizeof(t_env));
	if ((env->nb_usr = ft_parse(argc, argv, fd)) < 1)
		return (-1);//close fd if error;
	env->nb_process = env->nb_usr;
	if (ft_load(fd, env))
		return (-1); //free if error
	if (ft_run(mem, env))
		return (-1);
	return (0);
}
