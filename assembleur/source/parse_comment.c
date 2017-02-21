/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:55:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/19 17:48:42 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define LEN_COMMENT 8
#define LEN_COMMENT_EMPTY 11

void		check_if_comment_valid(char *str)
{
	int		i;
	uint8_t	nb_double_quote;

	i = 0;
	nb_double_quote = 0;
	while (str[i])
	{
		if (nb_double_quote >= 2)
			break ;
		if (str[i] == '\"')
			++nb_double_quote;
		++i;
	}
	if (nb_double_quote != 2)
		error(BAD_COMMENT);
	i += skip_blank(&str[i]);
	if (str[i] != ';' && str[i] != '#' && str[i] != '\0')
		error(BAD_COMMENT);
}

static int	check_error_comment(char *stock_comment)
{
	int		space_before_comment;
	int		space_after_comment;
	char	after_quote;
	int		len_comment;
	int		comment_start;

	space_before_comment = skip_blank(stock_comment);
	if (ft_strncmp(&stock_comment[space_before_comment],\
		".comment", LEN_COMMENT) != 0)
		error(COMMENT_NOT_FOUND);
	space_after_comment = skip_blank(&stock_comment[space_before_comment]\
	+ LEN_COMMENT);
	comment_start = space_before_comment + LEN_COMMENT \
		+ space_after_comment + 1;
	len_comment = ft_strclen(&stock_comment[comment_start], '"');
	if (len_comment > COMMENT_LENGTH)
		error(LONG_COMMENT);
	after_quote = stock_comment[(comment_start + len_comment + 1)\
		+ skip_blank(&stock_comment[(comment_start + len_comment + 1)])];
	if (after_quote != COMMENT_CHAR_CROMA \
		&& after_quote != COMMENT_CHAR && after_quote != '\0')
		error(BAD_FORMAT);
	return (space_before_comment + LEN_COMMENT + space_after_comment);
}

static void	loop_parse_comment(int *fd, char **stock_comment)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	while (get_next_line(*fd, &line) > 0)
	{
		if (is_cmt(line) == true)
		{
			ft_strdel(&line);
			continue ;
		}
		if ((tmp = ft_strjoin(*stock_comment, line)) == NULL)
			error(MALLOC);
		ft_strdel(stock_comment);
		*stock_comment = tmp;
		if (ft_count_char(*stock_comment, '\"') >= 2)
		{
			free(line);
			break ;
		}
		ft_strdel(&line);
	}
	if (line == NULL)
		error(COMMENT_NOT_FOUND);
}

void		parse_comment(int *fd, t_header *header)
{
	char	*stock_comment;
	int		start_comment;

	stock_comment = NULL;
	loop_parse_comment(fd, &stock_comment);
	start_comment = check_error_comment(stock_comment);
	check_if_comment_valid(stock_comment);
	ft_memset(header->comment, 0, COMMENT_LENGTH + 1);
	if (stock_comment[start_comment + 1] == '\"' && ft_strlen(stock_comment)
			== LEN_COMMENT_EMPTY)
		ft_strcat(header->comment, "Default comment");
	else
		ft_strccat(header->comment, &stock_comment[start_comment + 1], '\"');
	ft_strdel(&stock_comment);
}
