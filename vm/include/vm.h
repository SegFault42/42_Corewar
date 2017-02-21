/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:00:48 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/21 15:04:26 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
********************************************************************************
**                                  INCLUDES                                  **
********************************************************************************
*/

# include "op.h"
# include "libft.h"
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <sys/stat.h>
# include <SDL2/SDL.h>
# include <sys/types.h>
# include <SDL2/SDL_ttf.h>
# include "SDL2/SDL_image.h"
# include "../libsdl/SDL2_mixer.framework/Versions/A/Headers/SDL_mixer.h"

/*
********************************************************************************
**                                   DEFINES                                  **
********************************************************************************
*/

# define OPS_NUMBER 20

# define LIVE 1
# define LD 2
# define ST 3
# define ADD 4
# define SUB 5
# define AND 6
# define OR 7
# define XOR 8
# define ZJMP 9
# define LDI 10
# define STI 11
# define FORK 12
# define LLD 13
# define LLDI 14
# define LFORK 15
# define AFF 16
# define JMP 17
# define CMP 18
# define DIV 19
# define MUL 20

# define SHOW_LIVE 1
# define SHOW_CYCLES 2
# define SHOW_OPERATIONS 4
# define SHOW_DEATHS 8
# define SHOW_PC_MOVES 16

# define BYTES_BY_LINE 32
# define ADDRESS_MAX 65536

# define ERROR (-1)
# define INIT_VIDEO_ERROR (1)
# define CREATE_WINDOW_ERROR (2)

# define WIDTH (1920)
# define HEIGHT (1080)

# define ORIGIN_TEXT_X (20)
# define ORIGIN_TEXT_Y (15)
# define INCR_TEXT_X (20)
# define INCR_TEXT_Y (15)
# define GREY_TEXT (-1)
# define GREEN_TEXT (-2)
# define PURPLE_TEXT (-3)
# define P_TEXT (-3)
# define CYAN_TEXT (-4)
# define YELLOW_TEXT (-5)
# define Y_TEXT (-5)

/*
********************************************************************************
**                                   TYPEDEF                                 **
********************************************************************************
*/

typedef struct s_pos			t_pos;
typedef struct s_sound			t_sound;
typedef struct s_instruction	t_instruction;
typedef struct s_op				t_op;
typedef struct s_process		t_process;
typedef struct s_player			t_player;
typedef struct s_env			t_env;
typedef struct s_wallpaper		t_wallpaper;
typedef struct s_win			t_win;
typedef struct s_font			t_font;
typedef struct s_sdl			t_sdl;
typedef void(*t_func)(t_env*, t_process*);

/*
********************************************************************************
**                                 STRUCTURES                                 **
********************************************************************************
*/

struct		s_pos
{
	int		x;
	int		y;
};

struct		s_sound
{
	Mix_Music	*music;
	Mix_Chunk	*chunk;
};

struct		s_instruction
{
	uint8_t		opcode;
	uint8_t		ocp;
	uint8_t		param[3];
	uint32_t	val[3];
	int			n_cycle;
	int			bad_ocp;
	int			i;
};

struct		s_op
{
	char		*name;
	uint8_t		nb_arg;
	uint8_t		arg[3];
	uint8_t		opcode;
	uint16_t	n_cycle;
	char		*description;
	bool		carry;
	bool		direct;
};

struct		s_process
{
	t_instruction	inst;
	uint32_t		player_id;
	uint32_t		id;
	uint16_t		live;
	bool			carry;
	uint16_t		start;
	uint16_t		pc;
	int				reg[REG_NUMBER];
};

struct		s_player
{
	uint16_t	live;
	t_header	header;
	uint8_t		*op;
};

struct		s_wallpaper
{
	SDL_Surface		*wallpaper;
	SDL_Texture		*texture;
};

struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	uint16_t		delay;
	int8_t			color;
};

struct		s_font
{
	uint8_t			font_size;
	TTF_Font		*font;
	SDL_Color		text_color;
	SDL_Surface		*text;
	SDL_Texture		*texture;
	SDL_Rect		text_rect;
};

struct		s_sdl
{
	t_win		win;
	t_font		font[3];
	SDL_Event	event;
	t_wallpaper	wallpaper;
	t_sound		sound;
};

struct		s_env
{
	bool		run;
	uint32_t	nb_player;
	uint32_t	nb_process;
	int			cur_process;
	uint32_t	cycle;
	int			cur_die;
	int			cycle_die;
	uint32_t	check;
	uint32_t	alives;
	uint32_t	lives;
	uint32_t	valid_lives;
	uint32_t	last_live;
	t_player	*player;
	t_list		*process;
	uint8_t		verbose;
	uint32_t	dump;
	uint32_t	sdump;
	bool		fdf;
	bool		gui;
	bool		op_pause;
	uint32_t	player_id[MAX_PLAYERS];
	t_sdl		sdl;
};

/*
********************************************************************************
**                                  VARIABLES                                 **
********************************************************************************
*/

uint8_t		g_mem[MEM_SIZE];
uint32_t	g_color[MEM_SIZE];
uint32_t	g_pc[MEM_SIZE];

/*
********************************************************************************
**                                  FUNCTIONS                                 **
********************************************************************************
*/

void		init_memory(void);
void		init_instruction(t_instruction *inst);
void		init_processes(t_env *e);
void		init_env(t_env *e);
void		init_players(t_env *e);
void		init_vm(t_env *e, int argc, char **argv);
void		init_sdl_gui(t_sdl *sdl);
void		init_sdl_fdf(t_sdl *sdl);
uint32_t	ft_straight_bytes(unsigned int bytes);
void		ft_straight_header(t_header *header, t_env *env);
void		ft_load(uint8_t fd[MAX_PLAYERS], t_env *env);
int			ft_parse(t_env *e, int argc, char **argv, uint8_t fd[MAX_PLAYERS]);

uint8_t		get_mem_uint8(t_process *process, uint16_t index);
uint16_t	get_mem_uint16(t_process *process, uint16_t index);
uint32_t	get_mem_uint32(t_process *process, uint16_t index);
void		set_mem_uint8(t_process *process, uint16_t index, uint8_t val);
void		set_mem_uint16(t_process *process, uint16_t index, uint16_t val);
void		set_mem_uint32(t_process *process, uint16_t index, uint32_t val);
void		dump_memory(t_env *e);

uint32_t	src_param(t_process *proc, bool idx, uint8_t i, bool v_reg);
void		dst_param(t_process *proc, uint8_t i, uint32_t dest, uint32_t val);
void		fork_process(t_env *e, t_process *proc, uint16_t pc);
void		del_process(t_list *process, int id);
void		pc_moves(t_process *proc, int i);
int			idx_address(int val);
int			mem_address(int val);
int			get_address(int val);
void		ft_putnbr_hex(int octet, int rem);
bool		valid_reg(uint8_t reg);
bool		valid_params(t_process *proc);
int			valid_player(t_env *e, uint32_t id);
void		get_values(t_process *proc, t_instruction *inst);
void		wait_enter(t_env *e);
void		check_instruction(t_env *e, t_process *p);

void		exec_instruction(t_env *e, t_process *proc);
void		exec_live(t_env *e, t_process *proc);
void		exec_ld(t_env *e, t_process *proc);
void		exec_st(t_env *e, t_process *proc);
void		exec_add(t_env *e, t_process *proc);
void		exec_sub(t_env *e, t_process *proc);
void		exec_and(t_env *e, t_process *proc);
void		exec_or(t_env *e, t_process *proc);
void		exec_xor(t_env *e, t_process *proc);
void		exec_zjmp(t_env *e, t_process *proc);
void		exec_ldi(t_env *e, t_process *proc);
void		exec_sti(t_env *e, t_process *proc);
void		exec_fork(t_env *e, t_process *proc);
void		exec_lld(t_env *e, t_process *proc);
void		exec_lldi(t_env *e, t_process *proc);
void		exec_lfork(t_env *e, t_process *proc);
void		exec_aff(t_env *e, t_process *proc);
void		exec_jmp(t_env *e, t_process *proc);
void		exec_cmp(t_env *e, t_process *proc);
void		exec_div(t_env *e, t_process *proc);
void		exec_mul(t_env *e, t_process *proc);

int			check_ocp(t_process *proc, uint8_t ocp);
int			check_opcode(t_process *proc, uint8_t opcode);
t_op		get_op(int i);
t_env		*get_env(void);
void		run(t_env *e, t_sdl *sdl);

void		die(t_env *e, char *error);
void		free_env(t_env *e);

/*
********************************************************************************
**                                     GUI                                    **
********************************************************************************
*/

void		gui(t_env *e, t_sdl *sdl);
void		error(uint8_t error);
void		create_window(t_win *win);
void		close_window(t_win *win, int8_t error);
/*
** font.c
*/
void		init_ttf(t_win *win);
void		select_font(t_win *win, t_font *font, char *str);
void		draw_text(t_font *font, t_win *win, char *str, int i);

void		draw_memory(t_win *win, t_font *font);

void		screenshot(t_win *win, t_sdl *sdl);
void		print_wallpaper(t_wallpaper *wallpaper, t_win *win, char *path);
bool		button_press(SDL_Event *event, t_win *win,
		t_sdl *sdl);

void		change_text_color(SDL_Color text_color, uint8_t r, uint8_t g,
		uint8_t b);
void		general_info(t_font *font_general, t_win *win);

char		*write_lives(t_env *env);
char		*cycle_to_die(t_env *env);
char		*process_alives(t_env *env);
char		*max_check(t_env *env);

void		init_sound(t_sound *sound);
void		fdf(t_env *env, t_sdl *sdl);
void		general_info(t_font *font_general, t_win *win);
void		write_challengers(t_font *font_general, t_win *win);
void		write_general_info(t_font *font_general, t_env *env, t_win *win);
/*
** gui2.c
*/
void		error(uint8_t error);
void		close_window(t_win *win, int8_t error);
void		change_text_color(SDL_Color text_color,
		uint8_t r, uint8_t g, uint8_t b);
void		fill_octet(char *mem, uint8_t octet);

#endif
