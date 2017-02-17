/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 12:55:16 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/17 22:46:36 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int	ft_strcmp_ext(char *str, char *ext)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0 && str[i] != '.')
		--i;
	if (ft_strcmp(&str[i], ext) == 0)
		return (0);
	return (1);
}
