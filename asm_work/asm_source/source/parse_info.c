/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:45:54 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/23 17:29:13 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

int			parse_info(t_glob *glob, char *line, int fd)
{
	t_info	*tmp;

	(void)glob;
	(void)line;
	(void)fd;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = new_info()))
		return (MALLOC);
	return (TRUE);
}
