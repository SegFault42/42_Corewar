/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:57:06 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 22:31:28 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns a “fresh” string ending
**     with ’\0’. Each character of the string is initialized at
**     ’\0’. If the allocation fails the function returns NULL.
*/

char	*ft_strnew(size_t size)
{
	char	*space;
	size_t	i;

	i = 0;
	if ((space = malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	while (i < size)
	{
		space[i] = '\0';
		++i;
	}
	return (space);
}
