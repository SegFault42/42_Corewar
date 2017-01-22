/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/21 19:23:58 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <SDL2/SDL.h>
# include <sys/types.h>
# include <SDL2/SDL_ttf.h>
# include "../libft/includes/libft.h"

#define ERROR (-1)
#define INIT_VIDEO_ERROR (1)
#define CREATE_WINDOW_ERROR (2)

#define WIDTH 1280
#define HEIGHT 720

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
}					t_win;

typedef struct		s_font
{
	TTF_Font		*font;
}					t_font;

void	gui();
void	error(uint8_t error);
void	create_window(t_win *win);
void	sdl_clear(t_win *win);
void	close_window(t_win *win, int8_t error);
void	init_ttf(t_win *win, t_font *font);

#endif
