/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:07:44 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/23 17:17:38 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "functions.h"

/*
** Fonction de calcule de l'opc, bien verifier que les parametres soient
** valident et que le char ** ne fasse pas plus de 3
*/

unsigned char		ocp_calc(char **tab)
{
	int				i;
	unsigned char	ocp;

	i = 0;
	ocp = 0;
	while (tab[i])
	{
		if (is_reg(tab[i]))
			ocp += T_REG;
		else if (is_direct(tab[i]))
			ocp += T_DIR;
		else if (is_ind(tab[i]))
			ocp += T_IND;
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
