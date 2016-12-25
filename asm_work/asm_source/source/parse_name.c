/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/19 17:58:50 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	check_error_name(char *stock_name)
{
	int		len_name; // longueur de stock_name
	char	after_quote; // stock le caractere apres .comment (sauf caractere vide (' ' '\t'))

	len_name = ft_strclen(&stock_name[7], '"'); // compte le nombre de charactere entre les " de .name
	after_quote = stock_name[11 + len_name + skip_blank(&stock_name[11 + len_name])];
	if (len_name > PROG_NAME_LENGTH)
		error(LONG_NAME);
	if (stock_name[8 + len_name + skip_blank(&stock_name[8 + len_name])] != COMMENT_CHAR_CROMA &&
		stock_name[8 + len_name + skip_blank(&stock_name[8 + len_name])] != COMMENT_CHAR &&
		stock_name[8 + len_name + skip_blank(&stock_name[8 + len_name])] != '\0') // verfie si un caractere indesirable traine (lol)
		error(BAD_FORMAT);
}

// La fonction parse_name sert a verifier puis ecrire le le nom du programme dans le .cor
void	parse_name(int *fd, t_header *header)
{
	char	*line; // stock ce que lis gnl
	char	*stock_name; // stock la ligne de .name

	line = NULL;
	stock_name = NULL;
	while (get_next_line(*fd, &line) > 0) // premiere lecture avec gnl
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		stock_name = ft_strjoin(stock_name, line); // concatene ligne
		if (ft_count_char(stock_name, '\"') >= 2) // stop gnl a partir de la quote fermante de .name
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	check_error_name(stock_name);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1); // mise a NULL "header->prog_name"
	ft_strccat(header->prog_name, &stock_name[7], '\"'); // copie le nom du progamme dans "header->prog_name"
	ft_strdel(&stock_name);
}
