/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/16 18:15:02 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ignore_comment(int *fd)
{
	char	*line;

	while (get_next_line(*fd, &line) > 0)
	{
		if (line[0] == COMMENT_CHAR)
			continue ;
		else
			break ;
	}
}

int8_t	parse_s_file(char *file, t_header *header)
{
	int	fd;

	/*ft_fprintf(1, "%s\n", file);*/
	if ((fd = open(file, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	parse_comment(&fd, header);
	return (EXIT_SUCCESS);
}
