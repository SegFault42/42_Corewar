/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:14:52 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/23 15:20:31 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include <stdlib.h>

t_info	*new_info(void)
{
	t_info	*new;

	new = (t_info *)ft_memalloc(sizeof(t_info));
	return (new);
}
