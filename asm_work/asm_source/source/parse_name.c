/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/18 17:42:32 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

// La fonction parse_name sert a verifier puis ecrire le le nom du programme dans le .cor
void	parse_name(int *fd, t_header *header)
{
	char			*line; // stock ce que lis gnl
	int				nb_line; // compte le nombre de lecture de gnl
	char			str[136 + 1]; // stock le nom du programme a partir de ".name" jusqu'a '"'
	uint8_t			nb_char; // compte le nombre de caractere que gnl a stocke dans line
	int				nb_quote; // Pour compter le nombre de '"'

	nb_quote = 0;
	nb_line = 0;
	nb_char = 0;
	ft_memset(str, 0, 137);
	line = NULL;
	ignore_comment(fd);
	while (get_next_line(*fd, &line) > 0) // premiere lecture avec gnl
	{
		ft_fprintf(1, PURPLE"%s\n"END, line);
		ft_strdel(&line);
	}
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1); // mise a NULL "header->prog_name"
	ft_strccat(header->prog_name, &str[7], '\"'); // copie le nom du progamme dans "header->prog_name"
}
