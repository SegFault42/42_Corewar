/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:36:57 by lfabbro           #+#    #+#             */
/*   Updated: 2015/12/03 16:40:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t b)
{
	int		len;
	int		i;
	char	*dup;

	len = ft_strlen(s1);
	i = 0;
	dup = (char *)malloc(sizeof(*dup) * b + 1);
	if (dup == NULL)
		return (0);
	while ((size_t)i < b && i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
