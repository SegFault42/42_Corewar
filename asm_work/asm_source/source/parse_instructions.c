/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/12 19:23:21 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static bool	check_if_label_exist(char *line)
{
	int	i;

	i = skip_blank(line);
	while (line[i] != ':')
	{
		if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
			return (false);
		++i;
	}
		return (true);
}

void	check_label(int *fd)
{
	char	*line;

	while (get_next_line(*fd, &line) > 0)
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		if (check_if_label_exist(line) == false)
			error(BAD_LABEL_FORMAT);
		ft_fprintf(1, YELLOW"%s\n"END, line);
		ft_strdel(&line);
	}
}
