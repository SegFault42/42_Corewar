/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:07:44 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/27 10:03:12 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "functions.h"

/*
** Fonction de calcule de l'opc, bien verifier que les parametres soient
** valident et que le char ** ne fasse pas plus de 3
*/

int					check_ocp(t_op *tab, unsigned char ocp, uint8_t opcode)
{
	int				i;
	uint8_t			j;
	uint8_t			len;
	int				test;

	j = 0;
	i = search(opcode, tab);
	if (i < 0)
		return (OCP);
	len = tab[i].nb_arg;
	ocp >>= 2;
	while (j < len)
	{
		test = tab[i].arg_value[j] & ocp;
		ft_putnbr(ocp);
		ft_putendl("");
		// if (!test)
		// 	return (OCP);
		ocp >>= 2;
		j++;
	}
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
