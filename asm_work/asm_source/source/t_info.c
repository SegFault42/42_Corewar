/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_info.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:14:52 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/25 11:38:17 by hboudra          ###   ########.fr       */
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
	new->opcode = 0;;
	new->ocp = 0;
	return (new);
}
