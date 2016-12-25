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

static void	check_error_comment(char *stock_comment)
{
	int		len_comment; // longueur de stock_comment
	char	after_quote; // stock le caractere apres .comment (sauf caractere vide (' ' '\t'))

	len_comment = ft_strclen(&stock_comment[10], '"'); // compte le nombre de charactere entre les " de .name
	after_quote = stock_comment[11 + len_comment + skip_blank(&stock_comment[11 + len_comment])];
	if (len_comment > COMMENT_LENGTH)
		error(LONG_COMMENT);
	if (after_quote != COMMENT_CHAR_CROMA && after_quote != COMMENT_CHAR &&
		after_quote != '\0') // verfie si un caractere indesirable traine (lol)
		error(BAD_FORMAT);
}

void	parse_comment(int *fd, t_header *header)
{
	char	*line; // stock ce que lis gnl
	char	*stock_comment; // stock la ligne de .comment

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
	check_error_comment(stock_comment);
	ft_memset(header->comment, 0, COMMENT_LENGTH + 1); // mise a NULL "header->comment"
	ft_strccat(header->comment, &stock_comment[10], '\"'); // copie le nom du progamme dans "header->comment"
	ft_strdel(&stock_comment);
}
