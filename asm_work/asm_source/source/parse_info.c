/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:45:54 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/26 15:31:17 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

void push_back(t_info **lst, t_info *new)
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

int		set_opcode(t_info *info, char *line, t_op *op_tab)
{
	int		i;
	int		j;

	j = skip_blank(line);
	i = 0;
	while (i < 16)
	{
		if (ft_strncmp(&line[j], op_tab[i].instruction_name,
				ft_strlen(op_tab[i].instruction_name)) == 0)
			info->opcode = op_tab[i].opcode;
		++i;
	}
	i = skip_alpha(&line[j]);
	return (i + j);
}

int			parse_info(t_glob *glob, char *line)
{
	t_info	*tmp;
	int		i;

	tmp = NULL;
	if (!(tmp = new_info()))
		return (MALLOC);
	i = set_opcode(tmp, line, glob->op_table);
	push_back(&glob->list, tmp);
	tmp->param = ft_strsplit(&line[i], ',');
	tmp->ocp = ocp_calc(tmp->param, tmp);
	return (TRUE);
}
