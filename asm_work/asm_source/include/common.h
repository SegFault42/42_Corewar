/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:36:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/19 17:57:13 by rabougue         ###   ########.fr       */
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

# define MAGIC "0000"
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

# define COREWAR_EXEC_MAGIC		0xea83f3

# define COMMENT				"/* :Prog_name:"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CHAR			'#'

# define PARSE_S_FILE			1
# define PARSE_NAME				2
# define LONG_NAME				3
# define CREATING_FILE_ERROR	4
# define ERROR_QUOTE			5
# define LONG_COMMENT			6
# define BAD_FORMAT				7

typedef struct		s_header
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			prog_name[PROG_NAME_LENGTH + 1];
}					t_header;
/*
** parse_s_file.c
*/
int8_t				parse_s_file(char *file, t_header *header);
/*
** main.c
*/
void				error(int error);

void				parse_name(int *fd, t_header *header);
void				parse_comment(int *fd, t_header *header);
void				ignore_comment(int *fd);

#endif
