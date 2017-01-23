/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:45:31 by framel            #+#    #+#             */
/*   Updated: 2017/01/23 15:55:30 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include "op.h"
#include "libft/Includes/libft.h"
#include <stdint.h>

typedef struct	s_env
{
	uint32_t	nb_process;
	uint32_t	nb_usr;
	uint32_t	cycle;
	header_t	*header;
	uint8_t		**process;
}				t_env;

#endif
