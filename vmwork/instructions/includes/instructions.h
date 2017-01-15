/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:00:48 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/15 18:17:02 by qhonore          ###   ########.fr       */
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

/*
************************************
**           STRUCTURES           **
************************************
*/

struct	s_instruction
{
	uint8_t		opcode;
	uint8_t		ocp;
	uint8_t		param1;// Type du parametre 1
	uint8_t		param2;// Type du parametre 2
	uint8_t		param3;// Type du parametre 3
	int			val1;// Valeur du parametre 1
	int			val2;// Valeur du parametre 2
	int			val3;// Valeur du parametre 3
	int			n_cycle;// Nombre de cycles avant exécution
	int			i;
};

struct	s_op
{
	char		*name;
	uint8_t		nb_arg;
	uint8_t		arg_value[3];
	uint8_t		opcode;
	uint16_t	n_cycle;
	char		*description;
	bool		carry;
	bool		direct;// taille d'un T_DIR (true -> 2, false -> 4)
	bool		ocp;// OCP présent ou non
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

uint8_t		get_mem_uint8(t_process *process, uint16_t index);
uint16_t	get_mem_uint16(t_process *process, uint16_t index);
void		set_mem_uint8(t_process *process, uint16_t index, uint8_t val);
void		set_mem_uint16(t_process *process, uint16_t index, uint16_t val);
void		dump_memory(t_process *proc);

t_op		get_op(int i);

#endif
