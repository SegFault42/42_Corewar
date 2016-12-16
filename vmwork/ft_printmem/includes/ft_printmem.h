/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:56:42 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/16 18:34:53 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTMEM
# define FT_PRINTMEM

# define HEAD_SIZE	(2048 + 128 + 16)
# define MAGIC_N	0xea83f3

# include "libft.h"

void		print_memory(const void *addr, size_t size);

#endif
