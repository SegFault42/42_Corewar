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
** Fonction de calcule de l'ocp, bien verifier que les parametres soient
** valident et que le char ** ne fasse pas plus de 3
*/

char	ocp_calc(char **tab)//, t_info *info)
{
	char	ocp;
	int	i;

	ocp = 0;
	i = 0;
	while (tab && tab[i])
		i++;
	if (i > 3)
		return (0);
	i = 0;
	while (tab && tab[i])
	{
	//	info->arg_value[i] = 0;
		if (is_reg(tab[i]))
			ocp |= 0x01;
		else if (is_direct(tab[i]))
			ocp |= 0x02;
		else if (is_ind(tab[i]))
			ocp |= 0x03;
		ocp <<= 2;
		i++;
	}
	while (i++ < 3)
		ocp <<= 2;
	return (ocp);
}
