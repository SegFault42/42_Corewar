/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/13 12:45:13 by rabougue         ###   ########.fr       */
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
	while (get_next_line(*fd, &line) > 0) // premiere lecture avec gnl
	{
		ft_fprintf(1, "%s\n\n", line);
		if (ft_strncmp(line, COMMENT_CMD_STRING, 8) == 0)
			break ;
		nb_quote += ft_count_char(line, '"');
		if (nb_quote > 2)
			error(ERROR_QUOTE);
		nb_char += ft_strlen(line); // calcul de la taille du nom du programme + .name ""
		if (nb_char > 136) // si la taille du nom du programme + le .name "" depasse 136, alors error.
			error(LONG_COMMENT);
		ft_strcat(str, line); //stock "line" dans "str"
		if (nb_line == 0 && ft_strncmp(line, NAME_CMD_STRING, 5) != 0) // Verification si ".name" exist.
			error(PARSE_NAME);
		++nb_line; // incremente le nombre de ligne
	}
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1); // mise a NULL "header->prog_name"
	ft_strccat(header->prog_name, &str[7], '\"'); // copie le nom du progamme dans "header->prog_name"
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
