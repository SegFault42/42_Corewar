/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:48:20 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/25 15:10:31 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int8_t	create_file(int *fd, char **file)
{
	int	i;

	i = 0;
	/*if (open(*file, O_RDONLY) > 0) // si un fichier .cor est deja cree on le supprime*/
	/*{*/
		/*ft_fprintf(1, "File exist\n");*/
		/*[>remove(*file);<]*/
	/*}*/
	if((*fd = open(*file, O_RDONLY | O_CREAT, S_IRWXU)) < 0) // Creation du fichier .cor
		error(CREATING_FILE_ERROR);
	close(*fd);
	return (EXIT_SUCCESS);
}

void	error(int error)
{
	if (error == LONG_NAME)
		ft_fprintf(2, RED"Champion name too long (Max length 128)\n"END);
	else if (error == LONG_COMMENT)
		ft_fprintf(2, RED"Champion comment too long (Max length 2048)\n"END);
	else if (error == CREATING_FILE_ERROR)
		ft_fprintf(2, RED"Creating file error.\n"END);
	else if (error == ERROR_QUOTE)
		ft_fprintf(2, RED"Too many '\"' in .name (Only 2 needed).\n"END);
	else if (error == BAD_FORMAT)
		ft_fprintf(2, RED"Bad format\n"END);
	else if (error == BAD_CHARACTERE)
		ft_fprintf(2, RED"Bad caractere\n"END);
	else if (error == BAD_LABEL_FORMAT)
		ft_fprintf(1, RED"Error label bad formatted.\nAllowed caractere : digit (0-9) alpha, (a-z) and underscore ('_').\n"END);
	else if (error == NAME_NOT_FOUND)
		ft_fprintf(1, RED".name missing\n"END);
	else if (error == COMMENT_NOT_FOUND)
		ft_fprintf(1, RED".comment missing\n"END);
	else if (error == INSTR_INEXIST)
		ft_fprintf(1, RED"Instruction not valid\n"END);
	else if (error == BAD_NUMBER_PARAM)
		ft_fprintf(1, RED"Wrong number argument in instruction\n"END);
	else
		ft_fprintf(2, RED"Error %d\n"END, error);
	exit(EXIT_FAILURE);
}

static void	write_magic_number(int *fd)
{
	lseek(*fd, 0, SEEK_SET); // magic number here
	ft_fprintf(*fd, "%c", 0);
	lseek(*fd, 1, SEEK_SET); // magic number here
	ft_fprintf(*fd, "%c", 234);
	lseek(*fd, 2, SEEK_SET); // magic number here
	ft_fprintf(*fd, "%c", 131);
	lseek(*fd, 3, SEEK_SET); // magic number here
	ft_fprintf(*fd, "%c", 243);
}

int	main(int argc, char **argv)
{
	char	*file;
	int		fd;
	/*char	magic[] = MAGIC;*/
	t_header	header;
	t_op		op_table[17];
	char str[2192] = {0};

	if (argc != 2)
		exit(EXIT_FAILURE);
	ft_memset(&header, 0, sizeof(header));
	init_op_table(op_table);
	if (parse_s_file(argv[1], &header) == EXIT_FAILURE)
		error(PARSE_S_FILE);
	//==========================Creation du .cor===============================
	file = (char *)ft_memalloc(sizeof(char) * (ft_strlen(argv[1])) + 2); //Alloc len (name of the output.s + len .cor - ".c")
	ft_strccat(file, argv[1], '.');
	ft_strcat(file, ".cor");
	create_file(&fd, &file);
	fd = open(file, O_RDWR);
	free(file);
	//===========================Ecriture des infos dans le .cor================
	write(fd, str, 2192);
	write_magic_number(&fd); // write magic_number
	lseek(fd, 4, SEEK_SET); // prog_name here
	ft_fprintf(fd, "%s", header.prog_name);
	lseek(fd, 132, SEEK_SET); // nb octet instruction here
	//nb instruction here
	lseek(fd, 140, SEEK_SET); // comment here
	ft_fprintf(fd, "%s", header.comment);
	close(fd);
	//=========================================================================
	/*ft_fprintf(1, GREEN".name = %s\n"END, header.prog_name);*/
	/*ft_fprintf(1, GREEN".comment = %s\n"END, header.comment);*/
	for (int i = 0; i < 17; ++i)
	{
		printf("%s, %d, %d, %d, %d, %s, %d, %d\n",
				op_table[i].instruction_name,
				op_table[i].nb_arg,
				op_table[i].arg_value[0],
				op_table[i].opcode,
				op_table[i].n_cycle,
				op_table[i].desc_instr,
				op_table[i].carry,
				op_table[i].dir_indir);
	}
	free_op_table(op_table);
	return (0);
}
