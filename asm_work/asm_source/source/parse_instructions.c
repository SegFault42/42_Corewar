/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/13 22:58:12 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*get_instruction(char *line, bool label_exist)
{
	int	i;

	i = skip_blank(line);
	if (label_exist == true)
	{
		while (line[i] != LABEL_END)
			++i;
		++i;
		if (line[i] == '\0')
			return (NULL);
		i += skip_blank(&line[i]);
	}
	if (check_if_instruction_exist(&line[i]) == false)
		error(INSTR_INEXIST);
	return (&line[i]);
}

static void	replace_line(char **line)
{
	char	*tmp;

	tmp = *line;
	if (ft_strchr(*line, ';') && !ft_strchr(*line, '#'))
	{
		*line = ft_strsub(*line, 0, ft_strchr(*line, ';') - *line);
		ft_strdel(&tmp);
	}
	else if (!ft_strchr(*line, ';') && ft_strchr(*line, '#'))
	{
		*line = ft_strsub(*line, 0, ft_strchr(*line, '#') - *line);
		ft_strdel(&tmp);
	}
	else if (ft_strchr(*line, ';') && ft_strchr(*line, '#'))
	{
		if (ft_strchr(*line, ';') > ft_strchr(*line, '#'))
			*line = ft_strsub(*line, 0, ft_strchr(*line, '#') - *line);
		else
			*line = ft_strsub(*line, 0, ft_strchr(*line, ';') - *line);
		ft_strdel(&tmp);
	}
}

static void	parse_label(t_glob *glob, char *line, bool *label_exist, int i)
{
	char	*label;
	t_label	content;
	t_list	*tmp;

	if ((label = check_if_label_exist(line)))
	{
		*label_exist = true;
		if (check_if_label_good_formatted(label) == false)
			error(BAD_LABEL_FORMAT);
		content.str = label;
		content.n_inst = i;
		if (!(tmp = ft_lstnew(&content, sizeof(content))))
			error(MALLOC);
		ft_lstadd(&glob->label, tmp);
	}
}

static void	help(char **line, int label_exist, t_glob *glob, int *i)
{
	char	*tmp;

	if ((tmp = get_instruction(*line, label_exist)))
	{
		if (parse_info(glob, tmp) != TRUE)
		{
			ft_strdel(line);
			error(MALLOC);
		}
		(*i)++;
	}
}

void		parse_instructions(int *fd, t_glob *glob)
{
	char	*line;
	char	*label;
	bool	label_exist;
	int		i;

	label = NULL;
	i = 0;
	while (get_next_line(*fd, &line) > 0)
	{
		label_exist = false;
		if (is_cmt(line) == true)
		{
			ft_strdel(&line);
			continue ;
		}
		else if (ft_strchr(line, '#') || ft_strchr(line, ';'))
			replace_line(&line);
		parse_label(glob, line, &label_exist, i);
		help(&line, label_exist, glob, &i);
		free(line);
	}
}
