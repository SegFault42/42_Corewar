/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/13 23:06:23 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define LEN_NAME 5

static int	check_error_name(char *stock_name)
{
	int		space_before_name;
	int		space_after_name;
	char	after_quote;
	int		len_name;
	int		name_start;

	space_before_name = skip_blank(stock_name);
	if (ft_strncmp(&stock_name[space_before_name], ".name", LEN_NAME) != 0)
		error(NAME_NOT_FOUND);
	space_after_name = skip_blank(&stock_name[space_before_name] + LEN_NAME);
	name_start = space_before_name + LEN_NAME + space_after_name + 1;
	len_name = ft_strclen(&stock_name[name_start], '"');
	if (len_name > PROG_NAME_LENGTH)
		error(LONG_NAME);
	after_quote = stock_name[(name_start + len_name + 1) \
	+ skip_blank(&stock_name[(name_start + len_name + 1)])];
	if (after_quote != COMMENT_CHAR_CROMA && after_quote != COMMENT_CHAR \
		&& after_quote != '\0')
		error(BAD_FORMAT);
	return (space_before_name + LEN_NAME + space_after_name);
}

void		parse_name(int *fd, t_header *header)
{
	char	*line;
	char	*stock_name;
	int		start_name;

	line = NULL;
	stock_name = NULL;
	while (get_next_line(*fd, &line) > 0)
	{
		if (is_cmt(line) == true)
		{
			ft_strdel(&line);
			continue ;
		}
		stock_name = ft_strjoin(stock_name, line);
		if (ft_count_char(stock_name, '\"') >= 2)
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	start_name = check_error_name(stock_name);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1);
	ft_strccat(header->prog_name, &stock_name[start_name + 1], '\"');
	ft_strdel(&stock_name);
}
