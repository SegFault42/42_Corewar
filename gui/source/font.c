/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:08:05 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/21 23:42:58 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	init_ttf(t_win *win, t_font *font)
{
	if (TTF_Init() == ERROR)
	{
		ft_fprintf(2, "%s\n", TTF_GetError());
		close_window(win, ERROR);
	}
	font->font = TTF_OpenFont("./font/VCR_OSD_MONO_1.001.ttf", 25);
}
