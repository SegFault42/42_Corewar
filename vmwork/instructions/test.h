/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:30:40 by quentin           #+#    #+#             */
/*   Updated: 2017/01/13 20:10:58 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

typedef struct s_instruction t_instruction;

struct s_instruction
{
	uint8_t		opcode;
	uint8_t		ocp;
	uint8_t		param1;
	uint8_t		param2;
	uint8_t		param3;
	int			val1;
	int			val2;
	int			val3;
	int			cycle;
};

#endif
