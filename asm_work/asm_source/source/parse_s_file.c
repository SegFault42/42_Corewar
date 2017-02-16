/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/23 15:42:19 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int8_t	parse_s_file(char *file, t_header *header, t_glob *glob)
{
	int	fd;

	if ((fd = open(file, O_RDWR)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	parse_comment(&fd, header);
	parse_instructions(&fd, glob);
	return (EXIT_SUCCESS);
}
