/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:45:54 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/23 16:47:44 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

void parse_info(t_glob *glob, char *line, int fd)
{
	(void)glob;
	(void)line;
	ft_putstr(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	ft_putnbr(fd);
	ft_putendl("");
}
