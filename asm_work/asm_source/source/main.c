/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:48:20 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/13 22:04:24 by jcazako          ###   ########.fr       */
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
