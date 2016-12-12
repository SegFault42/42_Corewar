#include "common.h"

int8_t	create_file(int *fd, char **file)
{
	int	i;

	i = 0;
	if (open(*file, O_RDONLY) > 0)
		ft_fprintf(1, "File exist\n");
	if((*fd = open(*file, O_RDONLY | O_CREAT, S_IRWXU)) < 0)
	{
		ft_fprintf(2, RED"Creating file error.\n"END);
		return (EXIT_FAILURE);
	}
	close(*fd);
	return (EXIT_SUCCESS);
}

void	error(int error)
{
	if (error == LONG_COMMENT)
		ft_fprintf(2, RED"Champion name too long (Max length 128)\n"END);
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
	for (int i = 0; i < 2192; ++i)
	{
		ft_fprintf(fd, "\0");
		lseek(fd, i, SEEK_SET);
	}
	ft_fprintf(fd, "i");
	lseek(fd, 0, SEEK_SET);
	ft_fprintf(fd, "%s", magic);
	ft_fprintf(fd, "%s", header.prog_name);
	/*lseek(fd, 4 + 128, SEEK_SET);*/
	/*ft_fprintf(fd, "0");*/
	close(fd);
	return (0);
}
