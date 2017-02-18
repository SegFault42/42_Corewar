/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:48:52 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/15 14:09:36 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_load(uint8_t fd[MAX_PLAYERS], t_env *env)
{
	uint32_t	i;

	i = -1;
	if (!(env->player = (t_player*)malloc(sizeof(t_player) * env->nb_player)))
		die(env, "malloc failure (env->player)");
	while (++i < env->nb_player)
		env->player[i].op = NULL;
	i = -1;
	while (++i < env->nb_player)
	{
		if (read(fd[i], &env->player[i].header, sizeof(t_header)) != \
		sizeof(t_header))
			die(env, "file is too short");
		ft_straight_header(&env->player[i].header, env);
		if (!(env->player[i].op = (uint8_t *)malloc(\
		env->player[i].header.prog_size * sizeof(uint8_t))))
			die(env, "malloc failure (env->player[i].op)");
		if (read(fd[i], env->player[i].op, env->player[i].header.prog_size) != \
		env->player[i].header.prog_size)
			die(env, "player has not good instructions's length");
		close(fd[i]);
	}
}

static int	check_player_id(t_env *e, uint32_t id, char **argv, int *j)
{
	int		fd;
	int		i;

	(*j)++;
	if (id && (fd = open(argv[*j + 1], O_RDONLY)) > 0)
	{
		close(fd);
		i = -1;
		while (++i < MAX_PLAYERS)
			if (e->player_id[i] == id)
				return (0);
		return (1);
	}
	return (0);
}

static int	next_id(t_env *e, uint32_t n)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (e->player_id[i] == n)
		{
			n++;
			i = -1;
		}
	return (n);
}

int			parse_options(t_env *e, int argc, char **argv, int n)
{
	int		i;

	i = 0;
	if (!ft_strcmp(argv[i], "-v") && i + 1 < argc && ft_isdigitstr(argv[i + 1]))
		e->verbose = ft_atoi(argv[++i]);
	if ((!ft_strcmp(argv[i], "-dump") || !ft_strcmp(argv[i], "-d"))
	&& i + 1 < argc && ft_isdigitstr(argv[i + 1]))
		e->dump = ft_atoi(argv[++i]);
	if (!ft_strcmp(argv[i], "-s") && i + 1 < argc && ft_isdigitstr(argv[i + 1]))
		e->sdump = ft_atoi(argv[++i]);
	if (!ft_strcmp(argv[i], "-n") && i + 2 < argc && ft_isdigitstr(argv[i + 1])
	&& check_player_id(e, ft_atoi(argv[i + 1]), argv, &i))
		e->player_id[n] = ft_atoi(argv[i]);
	if (!ft_strcmp(argv[i], "-g") && !e->fdf)
		e->gui = 1;
	if (!ft_strcmp(argv[i], "-f") && !e->gui)
		e->fdf = 1;
	if (!ft_strcmp(argv[i], "-p"))
		e->op_pause = 1;
	i++;
	return (i);
}

int			ft_parse(t_env *e, int argc, char **argv, uint8_t fd[MAX_PLAYERS])
{
	int			i;
	uint32_t	n;

	i = 1;
	n = 0;
	while (i < argc)
	{
		if (*argv[i] == '-')
			i += parse_options(e, argc - i, (argv + i), n);
		else if (i < argc)
		{
			if (n > MAX_PLAYERS)
				return (n);
			fd[n] = open(argv[i], O_RDONLY);
			if (fd[n] < 0)
				return (0);
			if (!(e->player_id[n]))
				e->player_id[n] = next_id(e, n + 1);
			n++;
			i++;
		}
	}
	return (n);
}
