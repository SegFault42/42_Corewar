/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_try_memalloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 01:23:44 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/11 01:27:43 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_try_memalloc(size_t size)
{
	if ((char *)ft_memalloc(size) == NULL)
	{
		ft_putendl_fd("Memory allocation failure !", 2);
		exit(-1);
	}
}
