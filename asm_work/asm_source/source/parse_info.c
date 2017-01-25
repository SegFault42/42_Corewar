/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:45:54 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/25 15:30:24 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

void		set_opcode(t_info *info, char *line, t_op *op_tab)
{
	int		i;
	int		j;

	j = skip_blank(line);
	i = 0;
	while (i < 16)
	{
		if (ft_strncmp(&line[j], op_tab[i].instruction_name,
				ft_strlen(op_tab[i].instruction_name)) == 0)
		{
			ft_putendl(op_tab[i].instruction_name);
			info->opcode = op_tab[i].opcode;
		}
		++i;
	}
}

int			parse_info(t_glob *glob, char *line)
{
	t_info	*tmp;

	(void)line;
	tmp = glob->list;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = new_info()))
		return (MALLOC);
	set_opcode(tmp, line, glob->op_table);
	ft_putnbr(tmp->opcode);
	return (TRUE);
}
