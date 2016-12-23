/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/19 17:33:24 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		skip_blank(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) == true)
		++i;
	return (i);
}

void	ignore_comment(int *fd)
{
	char	*line;
	int		nb;
	int		blank;

	while (get_next_line_lseek(*fd, &line, &nb) > 0)
	{
		/*++g_line;*/
		blank = skip_blank(line);
		ft_fprintf(1, YELLOW"%s\n"END, line);
		if (line[blank] == COMMENT_CHAR || line[blank] == '\0' || line[blank] == COMMENT_CHAR_CROMA)
		{
			ft_strdel(&line);
			continue ;
		}
		else
		{
			lseek(*fd, -ft_strlen(line) -nb , SEEK_CUR);
			ft_strdel(&line);
			ft_fprintf(1, "g_line = %d\n", g_line);
			return ;
		}
	}
}

int8_t	parse_s_file(char *file, t_header *header)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	/*parse_comment(&fd, header);*/
	return (EXIT_SUCCESS);
}
