/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/19 21:22:50 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define LEN_NAME 5
#define LEN_NAME_EMPTY 8

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

static void	help_norme(int *fd, int *line_ok, char **stock_name)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (get_next_line(*fd, &line) > 0)
	{
		*line_ok = 1;
		if (is_cmt(line) == true)
		{
			ft_strdel(&line);
			continue ;
		}
		if ((tmp = ft_strjoin(*stock_name, line)) == NULL)
			error(MALLOC);
		ft_strdel(stock_name);
		*stock_name = tmp;
		if (ft_count_char(*stock_name, '\"') >= 2)
		{
			free(line);
			break ;
		}
		ft_strdel(&line);
	}
	if (line == NULL)
		error(NAME_NOT_FOUND);
}

void		parse_name(int *fd, t_header *header)
{
	char	*stock_name;
	int		start_name;
	int		line_ok;

	stock_name = NULL;
	line_ok = 0;
	help_norme(fd, &line_ok, &stock_name);
	if (line_ok == 0)
		error(NAME_NOT_FOUND);
	start_name = check_error_name(stock_name);
	check_if_comment_valid(stock_name);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1);
	if (stock_name[start_name + 1] == '\"' &&
			ft_strlen(stock_name) == LEN_NAME_EMPTY)
		ft_strcat(header->prog_name, "Default name");
	else
		ft_strccat(header->prog_name, &stock_name[start_name + 1], '\"');
	ft_strdel(&stock_name);
}
