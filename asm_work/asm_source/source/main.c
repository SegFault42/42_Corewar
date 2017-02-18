/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:48:20 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/18 21:38:43 by rabougue         ###   ########.fr       */
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
	int		i;

	i = 0;
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
	int			fd;
	t_header	header;
	t_glob		glob;
	char		str[2192];
	char		*file;
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (check_name(argc, argv[i]))
			error(BAD_FILE);
		ft_bzero(str, 2192);
		ft_memset(&header, 0, sizeof(header));
		glob.list = NULL;
		glob.label = NULL;
		if (parse_s_file(argv[i], &header, &glob) == EXIT_FAILURE)
			error(PARSE_S_FILE);
		if (check(glob))
			error(BAD_ARGUMENT);
		fd = create_file(argv[i], &file);
		write(fd, str, 2192);
		write_magic_number(&fd);
		write_file(fd, header, glob);
		free_glob(&glob);
		ft_fprintf(1, "Writing output program to %s\n", file);
		free(file);
	}
	return (0);
}
