/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/12 20:23:33 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	parse_name(int *fd, t_header *header)
{
	char			*line;
	int				nb_line;
	char			str[136 + 1];
	uint8_t			nb_char;
	int				i;

	nb_line = 0;
	nb_char = 0;
	i = 0;
	ft_memset(str, 0, 137);
	while (get_next_line(*fd, &line) > 0)
	{
		nb_char += ft_strlen(line);
		if (nb_char > 136)
			error(LONG_COMMENT);
		if (nb_line == 0)
			ft_strcat(str, line);
		else
			ft_strcat(str, line);
		if (nb_line == 0 && ft_strncmp(line, ".name \"", 7) != 0)
			error(PARSE_NAME);
		++nb_line;
	}
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1);
	ft_strccat(header->prog_name, &str[7], '\"');
	ft_fprintf(1, GREEN"%s\n"END, header->prog_name);
	(void)header;
}

int8_t	parse_s_file(char *file, t_header *header)
{
	int	fd;

	/*ft_fprintf(1, "%s\n", file);*/
	if ((fd = open(file, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	return (EXIT_SUCCESS);
}
