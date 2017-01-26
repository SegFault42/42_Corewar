/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/26 22:51:21 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <math.h>
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
# include "../include/SDL2/SDL_image.h"

# define ERROR (-1)
# define INIT_VIDEO_ERROR (1)
# define CREATE_WINDOW_ERROR (2)

# define WIDTH (1920)
# define HEIGHT (1080)
# define MEM_SIZE (4096)

# define ORIGIN_TEXT_X (20) // coord ou le texte sera place en x
# define ORIGIN_TEXT_Y (15) // coord ou le texte sera place en y
# define INCR_TEXT_X (20) // espacement entre chaque octet en x
# define INCR_TEXT_Y (15) // espacement entre chaque octet en y

uint8_t	g_memory[MEM_SIZE];
uint8_t	g_memory_color[MEM_SIZE];

typedef struct		s_wallpaper
{
	SDL_Surface		*wallpaper;
	SDL_Texture		*texture;
}					t_wallpaper;

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	uint16_t		delay;
}					t_win;

typedef struct		s_font
{
	uint8_t			font_size;
	TTF_Font		*font;
	SDL_Color		text_color;
	SDL_Surface		*text;
	SDL_Texture		*texture;
	SDL_Rect		text_rect;
}					t_font;


typedef struct		s_env
{
	
	bool			run;
	uint32_t		nb_player;
	uint32_t		nb_process;
	int				cur_process;
	uint32_t		cycle;
}					t_env;

void	gui();
void	error(uint8_t error);
void	create_window(t_win *win);
void	close_window(t_win *win, int8_t error);
void	sdl_clear(t_win *win, uint8_t r, uint8_t g, uint8_t b);
/*
** font.c
*/
void	init_ttf(t_win *win);
void	select_font(t_win *win, t_font *font, char *str);
void	draw_text(t_font *font, t_win *win, char *str, int i);

void	draw_memory(t_win *win, t_font *font);

void	screenshot(t_win *win);
void	print_wallpaper(t_wallpaper *wallpaper, t_win *win, char *path);
bool	button_press(SDL_Event *event, t_wallpaper *wallpaper, t_win *win);

#endif
