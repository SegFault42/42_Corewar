/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:07:44 by hboudra           #+#    #+#             */
/*   Updated: 2017/02/16 18:01:44 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include "functions.h"

/*
** Fonction de calcule de l'ocp, bien verifier que les parametres soient
** valident et que le char ** ne fasse pas plus de 3
*/

static int	ch_reg(t_info *info, int i)
{
	if (g_op_tab[(int)info->opcode - 1].arg_value[i] & T_REG)
		return (1);
	else
		return (0);
}

static int	ch_ind(t_info *info, int i)
{
	if (g_op_tab[(int)info->opcode - 1].arg_value[i] & T_IND)
		return (1);
	else
		return (0);
}

static int	ch_dir(t_info *info, int i)
{
	if (g_op_tab[(int)info->opcode - 1].arg_value[i] & T_DIR)
		return (1);
	else
		return (0);
}

char		ocp_calc(t_info *info)
{
	char	ocp;
	int		i;

	ocp = 0;
	i = 0;
	while (info->param && info->param[i])
	{
		if (i > 2)
			return (0);
		if (is_reg(info->param[i]) && ch_reg(info, i))
			ocp |= 0x01;
		else if (is_direct(info->param[i]) && ch_dir(info, i))
			ocp |= 0x02;
		else if (is_ind(info->param[i]) && ch_ind(info, i))
			ocp |= 0x03;
		else
			error(BAD_ARGUMENT);
		ocp <<= 2;
		i++;
	}
	if (i != (int)g_op_tab[(int)info->opcode - 1].nb_arg)
		error(BAD_NUMBER_PARAM);
	while (i++ < 3)
		ocp <<= 2;
	return (ocp);
}
