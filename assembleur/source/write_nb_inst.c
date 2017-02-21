/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_nb_inst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 23:09:02 by jcazako           #+#    #+#             */
/*   Updated: 2017/02/13 23:09:04 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	write_nb_inst(t_info *info, int fd)
{
	long	i;

	i = 0;
	while (info)
	{
		i += count_byte_inst(info);
		info = info->next;
	}
	i = invert_8(i);
	write(fd, (char*)&i, sizeof(long));
}
