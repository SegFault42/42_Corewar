/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:07:44 by hboudra           #+#    #+#             */
/*   Updated: 2017/02/11 21:53:26 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "functions.h"

/*
** Fonction de calcule de l'opc, bien verifier que les parametres soient
** valident et que le char ** ne fasse pas plus de 3
*/

/*unsigned char		ocp_calc(char **tab, t_info *info)
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
}*/

char	ocp_calc(char **tab, t_info *info)
{
	char	ocp;
	int		i;

	ocp = 0;
	i = 0;
	while (tab && tab[i])
		i++;
	if (i > 2)
		return (0);
	i = 0;
	ft_putnbr(info->opcode);
	while (tab && tab[i])
	{
		ft_putchar('A');
		info->arg_value[i] = 0;
		if (is_reg(tab[i]))
			ocp |= 0x01;
		else if (is_direct(tab[i]))
			ocp |= 0x02;
		else if (is_ind(tab[i]))
			ocp |= 0x03;
		ocp <<= 2;
		i++;
		ft_putnbr(ocp);
		ft_putchar('\n');
	}
	ft_putendl("fin");
	while (i++ < 3)
		ocp <<= 2;
	//ft_putnbr(ocp);
	ft_putchar('\n');
	return (ocp);
}
