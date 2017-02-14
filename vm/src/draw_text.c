/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 06:02:34 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/14 19:42:37 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*cycle_to_die(t_env *env)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(env->cur_die);
	join = ft_strjoin(itoa, " / ");
	tmp = ft_strdup(join);
	ft_strdel(&itoa);
	ft_strdel(&join);
	itoa = ft_itoa(env->cycle_die);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&tmp);
	ft_strdel(&itoa);
	return (join);
}

char	*write_lives(t_env *env)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(env->lives);
	join = ft_strjoin(itoa, " (");
	ft_strdel(&itoa);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	itoa = ft_itoa(env->valid_lives);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&tmp);
	ft_strdel(&itoa);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	join = ft_strjoin(tmp, ") / ");
	ft_strdel(&tmp);
	itoa = ft_itoa(NBR_LIVE);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&tmp);
	ft_strdel(&itoa);
	return (join);
}

char	*process_alives(t_env *env)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(env->alives);
	join = ft_strjoin(itoa, " / ");
	ft_strdel(&itoa);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	itoa = ft_itoa(env->nb_process);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&itoa);
	ft_strdel(&tmp);
	return (join);
}

char	*max_check(t_env *env)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(env->check);
	join = ft_strjoin(itoa, " / ");
	ft_strdel(&itoa);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	itoa = ft_itoa(MAX_CHECKS);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&itoa);
	ft_strdel(&tmp);
	return (join);
}
