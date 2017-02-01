/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:00:48 by qhonore           #+#    #+#             */
/*   Updated: 2017/02/01 16:50:34 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
********************************************************************************
**                                  INCLUDES                                  **
********************************************************************************
*/

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>

/*
********************************************************************************
**                                   DEFINES                                  **
********************************************************************************
*/

# define OPS_NUMBER 16

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

# define SHOW_LIVE 1
# define SHOW_CYCLES 2
# define SHOW_OPERATIONS 4
# define SHOW_DEATHS 8
# define SHOW_PC_MOVES 16

# define BYTES_BY_LINE 64 // 32

/*
********************************************************************************
**                                   TYPEDEF                                 **
********************************************************************************
*/

typedef struct s_instruction	t_instruction;
typedef struct s_op	t_op;
typedef struct s_process	t_process;
typedef struct s_player	t_player;
typedef struct s_env	t_env;
typedef void(*t_func)(t_env*, t_process*);

/*
********************************************************************************
**                                 STRUCTURES                                 **
********************************************************************************
*/

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
	t_instruction	inst;// Instruction en cours de traitement
	uint8_t			player_id;// ID du createur (Pour la couleur)
	uint16_t		live;// Nombre de live pour depuis cycle_die (valide ou non)
	bool			alive;// Processus en vie ou non
	bool			carry;// Carry (0 ou 1)
	uint16_t		start;// Position de depart
	uint16_t		pc;// PC (a cumuler avec start pour la position reel)
	int				reg[REG_NUMBER];// registres
};

struct		s_player
{
	uint16_t	live;// Nombre de lives valides depuis cycle_die
	t_header	header;// Infos du joueur (header_t)
	uint8_t		*op;// Programme initial
};

struct		s_env
{
	bool		run;
	uint32_t	nb_player;// Nombre de joueurs
	uint32_t	nb_process;// Nombre de processus
	int			cur_process;// Processus en cours d'execution
	uint32_t	cycle;// Nombre de cycles totaux
	int			cur_die;// Nombre actuel / CYCLE_TO_DIE (cur_die/cycle_die)
	int			cycle_die;// CYCLE_TO_DIE actuel
	uint32_t	check;// Nombre de checks / MAX_CHECKS
	uint32_t	alives;// Nombre de processus en vie
	uint32_t	lives;// Nombre de lives / NBR_LIVE
	uint32_t	valid_lives;// Nombre de lives valide (>= 1 && <= nb_player)
	uint32_t	last_live;// Dernier live valide (ex: 0xfffffffe)
	t_player	*player;// Tableau des joueurs
	t_process	*process;// Tableau des processus
	uint8_t		verbose;// Bonus -v (1|2|4|8|16) (cumulables: 12 = 8 + 4)
	uint32_t	dump;// Dump de la memoire -d [cycle du dump]
};

/*
********************************************************************************
**                                  VARIABLES                                 **
********************************************************************************
*/

uint8_t	g_mem[MEM_SIZE];
uint8_t	g_color[MEM_SIZE];

/*
********************************************************************************
**                                  FUNCTIONS                                 **
********************************************************************************
*/

void		init_memory(void);
void		init_instruction(t_instruction *inst);
void		init_processes(t_env *e);
void		init_env(t_env *e);

int			check_ocp(t_process *proc, uint8_t ocp);
t_op		get_op(int i);

uint8_t		get_mem_uint8(t_process *process, uint16_t index);
uint16_t	get_mem_uint16(t_process *process, uint16_t index);
uint32_t	get_mem_uint32(t_process *process, uint16_t index);
void		set_mem_uint8(t_process *process, uint16_t index, uint8_t val);
void		set_mem_uint16(t_process *process, uint16_t index, uint16_t val);
void		set_mem_uint32(t_process *process, uint16_t index, uint32_t val);
void		dump_memory(t_env *e);
void		ft_putnbr_hex(int octet, int rem);

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

bool		valid_reg(uint8_t reg);
bool		valid_params(t_process *proc);
uint32_t	src_param(t_process *proc, bool idx, uint8_t i, bool v_reg);
void		dst_param(t_process *proc, uint8_t i, uint32_t dest, uint32_t val);
void		fork_process(t_env *e, t_process *proc, uint16_t pc);
void		pc_moves(t_process *proc, int i);
int			aff_address(int val);

int			ft_load(uint8_t fd[MAX_PLAYERS], t_env *env);
int			ft_parse(t_env *e, int argc, char **argv, uint8_t fd[MAX_PLAYERS]);

#endif
