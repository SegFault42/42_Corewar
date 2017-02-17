/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:14:52 by hboudra           #+#    #+#             */
/*   Updated: 2017/02/13 23:07:20 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include <stdlib.h>

t_info	*new_info(void)
{
	t_info	*new;

	if ((new = (t_info *)ft_memalloc(sizeof(t_info))) == NULL)
		return (NULL);
	new->next = NULL;
	new->opcode = 0;
	new->ocp = 0;
	return (new);
}
