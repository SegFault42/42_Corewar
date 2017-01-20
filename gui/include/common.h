/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/20 23:16:22 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
//#include "./op.h"

#define ERROR (-1)
#define INIT_VIDEO_ERROR (1)
#define CREATE_WINDOW_ERROR (2)

#define WIDTH 1280
#define HEIGHT 720

typedef struct	s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;

}				t_win;

void	gui();
void	error(uint8_t error);
void	create_window(t_win *win);
void	sdl_clear(t_win *win);
void	close_window(t_win *win);



#endif
