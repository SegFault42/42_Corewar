/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:07:44 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/27 17:24:16 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "functions.h"

/*
** Fonction de calcule de l'opc, bien verifier que les parametres soient
** valident et que le char ** ne fasse pas plus de 3
*/
static int			check_one_arg(t_info *info, int arg)
{
	info->ocp >>= 6;
	if ((arg & info->ocp) == 0)
		return (OCP);
	return (TRUE);
}

int					check_ocp(t_op *tab, t_info *info)
{
	int				i;
	uint8_t			j;
	int				len;
	int				test;

	j = 0;
	i = search(info->opcode, tab);
	len = tab[i].nb_arg;
	ft_putstr("linstruction------->              ");
	ft_putendl(tab[i].instruction_name);
	if (i < 0 || (size_t)len != char_tab_len(info->param))
		return (OCP);
	if (len == 1)
		return (check_one_arg(info, tab[i].arg_value[0]));
	while (j < len)
	{
		info->ocp >>= 2;
		test = tab[i].arg_value[len - 1] & info->ocp;
		ft_putstr("ocp ----->");
		ft_putnbr(info->ocp);
		ft_putendl("");
		ft_putnbr(tab[i].arg_value[j]);
		ft_putendl("");
		if (test == 0)
			return (OCP);
		len--;
	}
	// if (!tab[i].arg_value[j] & ocp)
	// 	return (FALSE);
	return (TRUE);
}

unsigned char		ocp_calc(char **tab, t_info *info)
{
	int				i;
	unsigned char	ocp;

	i = 0;
	ocp = 0;
	while (tab[i])
	{
		if (is_reg(tab[i]))
		{
			ocp += T_REG;
			info->arg_value[i] = T_REG;
		}
		else if (is_direct(tab[i]))
		{
			ocp += T_DIR;
			info->arg_value[i] = T_DIR;
		}
		else if (is_ind(tab[i]))
		{
			ocp += T_IND;
			info->arg_value[i] = T_IND;
		}
		ocp <<= 2;
		i++;
	}
	while (i < 3)
	{
		ocp <<= 2;
		i++;
	}
	return (ocp);
}
