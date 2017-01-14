/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:55:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/14 22:01:08 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define LEN_COMMENT 8 // taille de .comment

static int	check_error_comment(char *stock_comment)
{
	int		space_before_comment;
	int		space_after_comment;
	char	after_quote; // stock le caractere apres .comment (sauf caractere vide (' ' '\t'))
	int		len_comment; // longueur de stock_comment
	int		comment_start;

	space_before_comment = skip_blank(stock_comment); // compte le nombre d'espace avant .comment
	if (ft_strncmp(&stock_comment[space_before_comment], ".comment", LEN_COMMENT) != 0)
		error(COMMENT_NOT_FOUND);
	space_after_comment = skip_blank(&stock_comment[space_before_comment] + LEN_COMMENT); // compte le nombre d'espace apres .comment
	comment_start = space_before_comment + LEN_COMMENT + space_after_comment + 1; // se place sur le premier caractere du .comment
	len_comment = ft_strclen(&stock_comment[comment_start], '"'); // compte le nombre de charactere entre les " de .comment
	if (len_comment > COMMENT_LENGTH) // si la taille du .comment est superieur a 128, erreur
		error(LONG_COMMENT);
	after_quote = stock_comment[(comment_start + len_comment + 1) + skip_blank(&stock_comment[(comment_start + len_comment + 1)])]; // +1 pour skip le dernier '"'
	if (after_quote != COMMENT_CHAR_CROMA && after_quote != COMMENT_CHAR && after_quote != '\0') // verfie si apres la derniere '"' il y a un autre caractere qu'un commentaire.
		error(BAD_FORMAT);
	return (space_before_comment + LEN_COMMENT + space_after_comment);
}

void	parse_comment(int *fd, t_header *header)
{
	char	*line; // stock ce que lis gnl
	char	*stock_comment; // stock la ligne de .comment
	int		start_comment;

	line = NULL;
	stock_comment = NULL;
	while (get_next_line(*fd, &line) > 0) // premiere lecture avec gnl
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		stock_comment = ft_strjoin(stock_comment, line); // concatene ligne
		if (ft_count_char(stock_comment, '\"') >= 2) // stop gnl a partir de la quote fermante de .name
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	start_comment = check_error_comment(stock_comment);

	ft_fprintf(1, "%s\n", &stock_comment[start_comment]);
	ft_memset(header->comment, 0, COMMENT_LENGTH + 1); // mise a NULL "header->comment"
	ft_strccat(header->comment, &stock_comment[start_comment+ 1], '\"'); // copie le nom du progamme dans "header->comment"
	ft_strdel(&stock_comment);
}
