/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:00:48 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/18 00:04:24 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/*
************************************
**            INCLUDES            **
************************************
*/

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

/*
************************************
**             DEFINES            **
************************************
*/

# define OPS_NUMBER 16

/*
************************************
**             TYPEDEF           **
************************************
*/

typedef struct s_instruction	t_instruction;
typedef struct s_op	t_op;
typedef struct s_process	t_process;
typedef void(*t_func)(t_process*);

/*
************************************
**           STRUCTURES           **
************************************
*/

struct	s_instruction
{
	uint8_t		opcode;
	uint8_t		ocp;
	uint8_t		param[3];// Type des parametres
	uint32_t	val[3];// Valeur des parametres
	int			n_cycle;// Nombre de cycles avant exécution
	int			i;
};

struct	s_op
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

struct	s_process
{
	t_instruction	inst;// Instruction en cours d'execution
	bool			carry;
	uint16_t		start;// Point de départ du programme
	uint16_t		pc;
	int				reg[REG_NUMBER];
};

/*
************************************
**            VARIABLES           **
************************************
*/

uint8_t	g_mem[MEM_SIZE];

/*
************************************
**            FUNCTIONS           **
************************************
*/

void		init_memory(void);
void		init_instruction(t_instruction *inst);
void		init_process(t_process *process);

int			check_ocp(t_process *proc, uint8_t ocp);
t_op		get_op(int i);

uint8_t		get_mem_uint8(t_process *process, uint16_t index);
uint16_t	get_mem_uint16(t_process *process, uint16_t index);
uint32_t	get_mem_uint32(t_process *process, uint16_t index);
void		set_mem_uint8(t_process *process, uint16_t index, uint8_t val);
void		set_mem_uint16(t_process *process, uint16_t index, uint16_t val);
void		set_mem_uint32(t_process *process, uint16_t index, uint32_t val);
void		dump_memory(t_process *proc);

void		exec_live(t_process *proc);
void		exec_ld(t_process *proc);
void		exec_st(t_process *proc);

void		exec_sti(t_process *proc);
void		exec_instruction(t_process *proc);

#endif
