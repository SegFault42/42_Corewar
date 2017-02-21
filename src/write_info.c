/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 14:47:50 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/16 15:25:06 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	write_cycle_and_to_die(t_font *font_general, t_env *env, t_win *win)
{
	char	*str;

	str = NULL;
	font_general->text_rect.x = 1510;
	font_general->text_rect.y = 38;
	str = ft_itoa(env->cycle);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
	font_general->text_rect.x = 1500;
	font_general->text_rect.y = 83;
	str = cycle_to_die(env);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
}

static void	write_live_and_speed(t_font *font_general, t_env *env, t_win *win)
{
	char	*str;

	str = NULL;
	font_general->text_rect.x = 1410;
	font_general->text_rect.y = 129;
	str = write_lives(env);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
	font_general->text_rect.x = 1525;
	font_general->text_rect.y = 1015;
	str = ft_itoa(win->delay * -1);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
}

static void	write_process_alive(t_font *font_general, t_env *env, t_win *win)
{
	char	*str;

	str = NULL;
	font_general->text_rect.x = 1520;
	font_general->text_rect.y = 175;
	str = process_alives(env);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
}

static void	write_max_check(t_font *font_general, t_env *env, t_win *win)
{
	char	*str;

	str = NULL;
	font_general->text_rect.x = 1487;
	font_general->text_rect.y = 221;
	str = max_check(env);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
}

void		write_general_info(t_font *font_general, t_env *env, t_win *win)
{
	char	*str;

	str = NULL;
	write_cycle_and_to_die(font_general, env, win);
	write_live_and_speed(font_general, env, win);
	write_process_alive(font_general, env, win);
	write_max_check(font_general, env, win);
	font_general->text_rect.x = 1550;
	font_general->text_rect.y = 267;
	str = ft_itoa(env->last_live);
	draw_text(font_general, win, str, GREY_TEXT);
	ft_strdel(&str);
	SDL_DestroyTexture(font_general->texture);
}
