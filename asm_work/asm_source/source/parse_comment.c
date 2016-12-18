/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:55:03 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/18 17:42:12 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	parse_comment(int *fd, t_header *header)
{
	char			*line; // stock ce que lis gnl
	int				nb_line; // compte le nombre de lecture de gnl
	char			str[2058 + 1]; // stock le commentaire a partir de ".comment" jusqu'a '"'
	uint16_t		nb_char; // compte le nombre de caractere que gnl a stocke dans line
	int				nb_quote; // Pour compter le nombre de '"'

	nb_quote = 0;
	nb_line = 0;
	nb_char = 0;
	ft_memset(str, 0, 2059);
	lseek(*fd, 0, SEEK_SET);
	while (get_next_line(*fd, &line) > 0)
	{
		if (ft_strncmp(COMMENT_CMD_STRING, line, 8) == 0)
			break ;
	}
	ft_strcat(str, line); //stock "line" dans "str"
	nb_char += ft_strlen(line); // calcul de la taille du nom du programme + .name ""
	while (get_next_line(*fd, &line) > 0)
	{
		nb_quote += ft_count_char(line, '"');
		if (nb_quote > 2)
			error(ERROR_QUOTE);
		nb_char += ft_strlen(line); // calcul de la taille du nom du programme + .name ""
		if (nb_char > 2058) // si la taille du commentaire + le .comment "" depasse 2058, alors error.
			error(LONG_COMMENT);
		ft_strcat(str, line); //stock "line" dans "str"
		++nb_line; // incremente le nombre de ligne
	}
	(void)header;
}
