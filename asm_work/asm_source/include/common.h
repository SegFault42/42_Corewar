/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/30 17:11:52 by jcazako          ###   ########.fr       */
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

typedef struct		s_op
{
	char			*instruction_name;
	uint8_t			nb_arg;
	uint8_t			arg_value[4];
	uint8_t			opcode;
	uint16_t		n_cycle;
	char			*desc_instr;
	bool			carry;
	bool			dir_indir;
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

typedef struct		s_glob
{
	t_op 			op_table[17];
	t_info			*list;
}					t_glob;
/*
** parse_s_file.c
*/
unsigned char		ocp_calc(char **tab, t_info *info);
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
#endif
