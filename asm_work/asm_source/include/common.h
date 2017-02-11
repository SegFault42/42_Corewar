/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/11 21:31:16 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
//#include "./op.h"

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

# define COREWAR_EXEC_MAGIC		0xea83f3
# define BLANK_ZONE				0000

# define COMMENT				"/* :Prog_name:"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CHARS			";#"
# define COMMENT_CHAR			'#'
# define COMMENT_CHAR_CROMA		';'
# define LABEL_END				':'
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define DIRECT_CHAR			'%'

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

# define PARSE_S_FILE			1
# define PARSE_NAME				2
# define LONG_NAME				3
# define CREATING_FILE_ERROR	4
# define ERROR_QUOTE			5
# define LONG_COMMENT			6
# define BAD_FORMAT				7
# define BAD_CHARACTERE			8
# define BAD_LABEL_FORMAT		9
# define NAME_NOT_FOUND			10
# define COMMENT_NOT_FOUND		11
# define INSTR_INEXIST			12
# define BAD_NUMBER_PARAM		13
# define BAD_ARGUMENT			14
# define MALLOC					15

# define LIVE 0x01
# define LD 0x02
# define ST 0x03
# define ADD 0x04
# define SUB 0x05
# define AND 0x06
# define OR 0x07
# define XOR 0x08
# define ZJUMP 0x09
# define LDI 0x0a
# define STI 0x0b
# define FORK 0x0c
# define LLD 0x0d
# define LLDI 0x0e
# define LFORK 0x0f
# define AFF 0x10


typedef struct		s_op
{
	char			*instruction_name;
	uint8_t			nb_arg;
	uint8_t			arg_value[4];
	uint8_t			opcode;
	uint16_t		n_cycle;
	char			*desc_instr;
	bool			carry;
	bool			dir_indir;// false = 4, true = 2 
}					t_op;

typedef struct		s_header
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			prog_name[PROG_NAME_LENGTH + 1];
}					t_header;

typedef struct		s_info
{
	char			**param;
	char			opcode;
	unsigned char	ocp;
	uint8_t			arg_value[4];
	struct s_info	*next;
}					t_info;

typedef struct	s_label
{
	char	*str;
	int	n_inst;
}		t_label;

typedef struct		s_glob
{
	t_op 			op_table[17];
	t_list			*label;
	t_info			*list;
}					t_glob;

/*t_op	g_op_tab[] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},\
		6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},\
		11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{"jmp", 1, {T_DIR}, 17, 25, "jump", 0, 1},
	{"cmp", 2, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR},\
		18, 3, "cmp (val1 == val2)", 1, 0},
	{"div", 3, {T_REG, T_REG, T_REG}, 19, 20, "division", 1, 0},
	{"mul", 3, {T_REG, T_REG, T_REG}, 20, 20, "multiplication", 1, 0}
};*/

/*
 ** parse_s_file.c
 */
char				ocp_calc(char **tab, t_info *info);
int8_t				parse_s_file(char *file, t_header *header, t_glob *glob);
/*
 ** main.c
 */
void				error(int error);

void				parse_name(int *fd, t_header *header);
void				parse_comment(int *fd, t_header *header);
int 				parse_info(t_glob *glob, char *line);
/*
 ** tools.c
 */
int					skip_blank(char *line);
int					is_cmt(char *line);
int     			wordnb(char *str);
/*
 ** check_label.c
 */
void				parse_instructions(int *fd, t_glob *glob);
/*
 ** op_tab.c
 */
void				init_op_table(t_op *op_table);
void				free_op_table(t_op *op_table);
t_info				*new_info(void);


/*
 ** clear_line.c
 */
char    			*clear_line(char *str);


/*
 ** write_param.c
 */
void			write_param(int fd, t_glob glob);

/*
 ** count_byte_inst.c
 */
int			count_byte_inst(t_info *info);
/*
 ** get_label_val.c
 */
int     get_label_val(t_info *info, t_glob glob, int i);
/*
 ** invert.c
 */
int		invert_2(int i);
int		invert_4(int i);

#endif
