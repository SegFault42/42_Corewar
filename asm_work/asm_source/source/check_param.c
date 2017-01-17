/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 10:45:26 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/17 12:31:13 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

int		is_reg(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'r')
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
		if (!str[i])
			return (TRUE);
	}
	return (FALSE);
}

int		is_direct(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '%')
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
		if (!str[i])
			return (TRUE);
	}
	return (FALSE);
}

int		is_ind(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '%' && str[i + 1] == ':')
	{
		i += 2;
		while (ft_isalnum(str[i]))
			i++;
		if (!str[i])
			return (TRUE);
	}
	return (FALSE);
}
