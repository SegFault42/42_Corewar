/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:00:48 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/21 15:06:50 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

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

/*
********************************************************************************
**                                   DEFINES                                  **
********************************************************************************
*/

# define OPS_NUMBER 16

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
	uint8_t		param[3];// Type des parametres
	uint32_t	val[3];// Valeur des parametres
	int			n_cycle;// Nombre de cycles avant exécution
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
	bool		direct;// taille d'un T_DIR (true -> 2, false -> 4)
};

struct		s_process
{
	t_instruction	inst;// Instruction en cours d'execution
	bool			carry;
	uint16_t		start;// Point de départ du programme
	uint16_t		pc;
	int				reg[REG_NUMBER];
};

struct		s_player
{
	uint16_t	live;
	uint8_t		*op;
};

struct		s_env
{
	bool		run;
	uint32_t	nb_player;
	uint32_t	nb_process;
	uint32_t	cycle;
	t_player	*player;
	t_process	*process;
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

#endif
