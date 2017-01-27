/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 12:10:51 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/27 17:10:28 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	init_op_table(t_op *op_table)
{
	op_table[0] = (t_op){ft_strdup("live"), 1, {T_DIR}, 1, 10, ft_strdup("alive"), 0, 0};
	op_table[1] = (t_op){ft_strdup("ld"), 2, {T_DIR | T_IND, T_REG}, 2, 5, ft_strdup("load"), 1, 0};
	op_table[2] = (t_op){ft_strdup("st"), 2, {T_REG, T_IND | T_REG}, 3, 5, ft_strdup("store"), 1, 0};
	op_table[3] = (t_op){ft_strdup("add"), 3, {T_REG, T_REG, T_REG}, 4, 10, ft_strdup("addition"), 1, 0};
	op_table[4] = (t_op){ft_strdup("sub"), 3, {T_REG, T_REG, T_REG}, 5, 10, ft_strdup("soustraction"), 1, 0};
	op_table[5] = (t_op){ft_strdup("and"), 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, ft_strdup("et (and r1, r2, r3   r1&r2 -> r3"), 1, 0};
	op_table[6] = (t_op){ft_strdup("or"), 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, ft_strdup("ou  (or   r1, r2, r3   r1 | r2 -> r3"), 1, 0};
	op_table[7] = (t_op){ft_strdup("xor"), 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, ft_strdup("ou (xor  r1, r2, r3   r1^r2 -> r3"), 1, 0};
	op_table[8] = (t_op){ft_strdup("zjmp"), 1, {T_DIR}, 9, 20, ft_strdup("jump if zero"), 0, 1};
	op_table[9] = (t_op){ft_strdup("ldi"), 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, ft_strdup("load index"), 1, 1};
	op_table[10] = (t_op){ft_strdup("sti"), 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, ft_strdup("store index"), 1, 1};
	op_table[11] = (t_op){ft_strdup("fork"), 1, {T_DIR}, 12, 800, ft_strdup("fork"), 0, 1};
	op_table[12] = (t_op){ft_strdup("lld"), 2, {T_DIR | T_IND, T_REG}, 13, 10, ft_strdup("long load"), 1, 0};
	op_table[13] = (t_op){ft_strdup("lldi"), 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, ft_strdup("long load index"), 1, 1};
	op_table[14] = (t_op){ft_strdup("lfork"), 1, {T_DIR}, 15, 1000, ft_strdup("long fork"), 0, 1};
	op_table[15] = (t_op){ft_strdup("aff"), 1, {T_REG}, 16, 2, ft_strdup("aff"), 1, 0};
	op_table[16] = (t_op){NULL, 0, {0}, 0, 0, NULL, 0, 0};
}

void	free_op_table(t_op *op_table)
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		free(op_table[i].instruction_name);
		free(op_table[i].desc_instr);
		++i;
	}
}
