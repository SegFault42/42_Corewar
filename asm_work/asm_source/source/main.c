/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:48:20 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/19 17:56:50 by rabougue         ###   ########.fr       */
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
	else
		ft_fprintf(2, RED"Error %d\n"END, error);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	char	*file;
	int		fd;
	char	magic[] = MAGIC;
	t_header	header;
	char str[2192] = {0};

	if (argc != 2)
		exit(-1);
	ft_memset(&header, 0, sizeof(header));
	if (parse_s_file(argv[1], &header) == EXIT_FAILURE)
		error(PARSE_S_FILE);
	file = (char *)ft_memalloc(sizeof(char) * (ft_strlen(argv[1])) + 2);
	//Alloc len (name of the output.s + len .cor - ".c")
	ft_strccat(file, argv[1], '.');
	ft_strcat(file, ".cor");
	create_file(&fd, &file);
	fd = open(file, O_RDWR);
	write(fd, str, 2192);
	lseek(fd, 0, SEEK_SET); // magic number here
	ft_fprintf(fd, "%s", magic);
	lseek(fd, 4, SEEK_SET); // prog_name here
	ft_fprintf(fd, "%s", header.prog_name);
	lseek(fd, 132, SEEK_SET); // nb instruction here
	//nb instruction here
	lseek(fd, 140, SEEK_SET); // comment here
	//comment here
	close(fd);
	return (0);
}
