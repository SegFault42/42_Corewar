/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:50:35 by jcazako           #+#    #+#             */
/*   Updated: 2017/02/18 20:26:16 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void		del_label(t_label *ct, size_t ct_size)
{
	free(ct->str);
	ft_bzero(ct, ct_size);
	free(ct);
}

static void		free_tab(char **param)
{
	int		i;

	i = 0;
	while (param && param[i])
	{
		free(param[i]);
		param[i] = NULL;
		i++;
	}
	free(param);
}

static void		free_info(t_info **info)
{
	if (info && *info && (*info)->next)
		free_info(&(*info)->next);
	if (info && *info)
	{
		free_tab((*info)->param);
		free(*info);
		*info = NULL;
	}
}

void			free_glob(t_glob *glob)
{
	ft_lstdel(&glob->label, (void(*)(void*, size_t))del_label);
	free_info(&glob->list);
}
