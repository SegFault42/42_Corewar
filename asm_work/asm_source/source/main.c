/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:48:20 by rabougue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/01/18 20:10:30 by rabougue         ###   ########.fr       */
=======
/*   Updated: 2017/02/13 22:04:24 by jcazako          ###   ########.fr       */
>>>>>>> jcazako
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	write_file(int fd, t_header header, t_glob glob)
{
	lseek(fd, 4, SEEK_SET);
	ft_fprintf(fd, "%s", header.prog_name);
	lseek(fd, 132, SEEK_SET);
	write_nb_inst(glob.list, fd);
	lseek(fd, 140, SEEK_SET);
	ft_fprintf(fd, "%s", header.comment);
	lseek(fd, 0, SEEK_END);
	write_param(fd, glob);
	close(fd);
}

static int	create_file(char *arg, char **file)
{
<<<<<<< HEAD
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
=======
	int		fd;

	if (!(*file = ft_strnew(ft_strlen(arg) + 2)))
		error(MALLOC);
	ft_strccat(*file, arg, '.');
	ft_strcat(*file, ".cor");
	if ((fd = open(*file, O_RDWR | O_CREAT | O_EXCL, S_IRWXU)) < 0)
	{
		if (errno == EEXIST)
		{
			ft_fprintf(2, RED"%s already exist; erase it please.\n"END, *file);
			free(*file);
			exit(EXIT_FAILURE);
		}
		else
		{
			free(*file);
			error(CREATING_FILE_ERROR);
		}
	}
	return (fd);
>>>>>>> jcazako
}

static void	write_magic_number(int *fd)
{
	lseek(*fd, 0, SEEK_SET);
	ft_fprintf(*fd, "%c", 0);
	lseek(*fd, 1, SEEK_SET);
	ft_fprintf(*fd, "%c", 234);
	lseek(*fd, 2, SEEK_SET);
	ft_fprintf(*fd, "%c", 131);
	lseek(*fd, 3, SEEK_SET);
	ft_fprintf(*fd, "%c", 243);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_header	header;
	t_glob		glob;
	char		str[2192];
	char		*file;

	if (argc != 2)
		exit(EXIT_FAILURE);
	ft_bzero(str, 2192);
	ft_memset(&header, 0, sizeof(header));
	glob.list = NULL;
	glob.label = NULL;
	if (parse_s_file(argv[1], &header, &glob) == EXIT_FAILURE)
		error(PARSE_S_FILE);
	fd = create_file(argv[1], &file);
	write(fd, str, 2192);
	write_magic_number(&fd);
	write_file(fd, header, glob);
	ft_fprintf(1, "Writing output program to %s\n", file);
	free(file);
	free_glob(&glob);
	return (0);
}
