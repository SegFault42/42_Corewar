/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:45:54 by hboudra           #+#    #+#             */
/*   Updated: 2017/02/18 20:22:20 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

void		push_back(t_info **lst, t_info *new)
{
	t_info	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			skip_alpha(char *line)
{
	int		i;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	return (i);
}

int			set_opcode(t_info *info, char *line)
{
	int		i;
	int		j;

	j = skip_blank(line);
	i = 0;
	while (g_op_tab[i].instruction_name)
	{
		if (!ft_strncmp(&line[j], g_op_tab[i].instruction_name,\
			ft_strlen(g_op_tab[i].instruction_name)))
			info->opcode = g_op_tab[i].opcode;
		i++;
	}
	i = skip_alpha(&line[j]);
	return (i + j);
}

static int	count_comma(char *line)
{
	int	i;

	i = 0;
	while (line && *line)
		if (*line++ == ',')
			i++;
	return (i);
}

int			parse_info(t_glob *glob, char *line)
{
	t_info	*tmp;
	int		i;
	int		j;
	char	*box;

	tmp = NULL;
	if (!(tmp = new_info()))
		error(MALLOC);
	i = set_opcode(tmp, line);
	push_back(&glob->list, tmp);
	if (!(tmp->param = ft_strsplit(&line[i], ',')))
		error(MALLOC);
	j = 0;
	while (tmp->param[j])
	{
		if (j > 2 || count_comma(line) > 2)
			error(BAD_NUMBER_PARAM);
		box = tmp->param[j];
		tmp->param[j] = clear_line(tmp->param[j]);
		free(box);
		j++;
	}
	tmp->ocp = ocp_calc(tmp);
	return (TRUE);
}
