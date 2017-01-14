/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:00:48 by qhonore           #+#    #+#             */
/*   Updated: 2017/01/14 20:23:01 by qhonore          ###   ########.fr       */
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

/*
************************************
**           STRUCTURES           **
************************************
*/

struct	s_instruction
{
	uint8_t		opcode;
	uint8_t		ocp;
	uint8_t		param1;
	uint8_t		param2;
	uint8_t		param3;
	int			val1;
	int			val2;
	int			val3;
	int			n_cycle;
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
	bool		direct;
	bool		ocp;
};

/*
************************************
**            VARIABLES           **
************************************
*/

char	g_mem[MEM_SIZE];

/*
************************************
**            FUNCTIONS           **
************************************
*/

void	dump_memory(void);
t_op	get_op(int i);

#endif
