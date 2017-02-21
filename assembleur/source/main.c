/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:48:20 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/21 14:45:23 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	write_magic_number(int fd)
{
	lseek(fd, 0, SEEK_SET);
	ft_fprintf(fd, "%c", 0);
	lseek(fd, 1, SEEK_SET);
	ft_fprintf(fd, "%c", 234);
	lseek(fd, 2, SEEK_SET);
	ft_fprintf(fd, "%c", 131);
	lseek(fd, 3, SEEK_SET);
	ft_fprintf(fd, "%c", 243);
}

static void	write_file(int fd, t_header header, t_glob glob)
{
	write_magic_number(fd);
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
	int		i;

	if (!(*file = ft_strnew(ft_strlen(arg) + 2)))
		error(MALLOC);
	ft_strcat(*file, arg);
	i = ft_strlen(arg) - 1;
	(*file)[i] = 'c';
	ft_strcat(*file, "or");
	if ((fd = open(*file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		error(CREATING_FILE_ERROR);
	return (fd);
}

static int	check_name(int argc, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (str && --i >= 0 && str[i] == 's' && --i >= 0 && str[i] == '.')
		return (0);
	return (1);
	(void)argc;
}

int			main(int argc, char **argv)
{
	int			fd[2];
	t_header	header;
	t_glob		glob;
	char		str[2192];
	char		*file;

	ft_memset(fd, 0, sizeof(fd));
	while (++fd[1] < argc)
	{
		if (check_name(argc, argv[fd[1]]))
			error(BAD_FILE);
		ft_bzero(str, 2192);
		ft_memset(&header, 0, sizeof(header));
		glob.list = NULL;
		glob.label = NULL;
		if (parse_s_file(argv[fd[1]], &header, &glob) == EXIT_FAILURE)
			error(PARSE_S_FILE);
		fd[0] = create_file(argv[fd[1]], &file);
		write(fd[0], str, 2192);
		write_file(fd[0], header, glob);
		free_glob(&glob);
		ft_fprintf(1, "Writing output program to %s\n", file);
		free(file);
	}
	return (0);
}
