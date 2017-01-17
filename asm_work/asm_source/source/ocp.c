/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:07:44 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/17 17:34:00 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

unsigned char		ocp_calc(char **tab)
{
	int				len;
	int				i;
	unsigned char	ocp;

	i = 0;
	len = char_tab_len(tab);
	ocp = 0;
	ocp <<= 6;
	while (i < len)
	{
		if (is_reg(tab[i]))
			ocp += 1;
		else if (is_direct(tab[i]))
			ocp += 2;
		else if (is_ind(tab[i]))
			ocp += 3;
		ocp >>= 2;
		i++;
	}
	return (ocp);
}

int main(void)
{
	unsigned char test;
	char *tab[4];

	tab[0] = "r1";
	tab[1] = "%:live";
	tab[2] = "%2";
	tab[3] = NULL;
	test = ocp_calc(tab);
	ft_putnbr(test);
	return (0);
}
