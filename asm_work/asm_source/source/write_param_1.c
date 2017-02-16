/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 23:16:04 by jcazako           #+#    #+#             */
/*   Updated: 2017/02/15 23:15:19 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "functions.h"

void	write_reg(int fd, int i, t_info *info)
{
	int		tmp;
	char	*reg;

	reg = info->param[i];
	reg++;
	tmp = 0;
	if ((tmp = ft_atoi(reg)) > 99 || tmp < 0)
		error(BAD_ARGUMENT);
	write(fd, (char*)&tmp, T_REG);
}

void	write_dir(int fd, int i, t_info *info, t_glob glob)
{
	int		tmp;
	char	opcode;

	opcode = info->opcode;
	if (g_op_tab[opcode - 1].dir_indir)
	{
		if (!ft_strchr(info->param[i], (int)':'))
			tmp = invert_2(get_nbr(info->param[i] + 1));
		else
			tmp = invert_2(get_label_val(info, glob, i));
		write(fd, (char*)&tmp, T_DIR);
	}
	else
	{
		if (!ft_strchr(info->param[i], (int)':'))
			tmp = invert_4(get_nbr(info->param[i] + 1));
		else
			tmp = invert_4(get_label_val(info, glob, i));
		write(fd, (char*)&tmp, T_IND);
	}
}

void	write_ind(int fd, int i, t_info *info, t_glob glob)
{
	int		tmp;

	if (!ft_strchr(info->param[i], (int)':'))
		tmp = get_nbr(info->param[i]);
	else
		tmp = get_label_val(info, glob, i);
	tmp = invert_2(tmp);
	write(fd, (char*)&tmp, T_DIR);
}
