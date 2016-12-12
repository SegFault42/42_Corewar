#include "common.h"


int8_t	create_file(int *fd, char **file)
{
	if((*fd = open(*file, O_RDONLY | O_CREAT, S_IRWXU)) < 0)
	{
		ft_fprintf(2, RED"Creating file error.\n"END);
		return (EXIT_FAILURE);
	}
	close(*fd);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	char	*file;
	int		fd;
	char	magic[] = MAGIC;

	if (argc != 2)
		exit(-1);
	file = (char *)ft_memalloc(sizeof(char) * (ft_strlen(argv[1])) + 2);
	//Alloc len (name of the output.s + len .cor - ".c")
	ft_strccat(file, argv[1], '.');
	ft_strcat(file, ".cor");
	create_file(&fd, &file);
	fd = open(file, O_RDWR);
	ft_fprintf(fd, "%s", magic);
	ft_fprintf(fd, "%s", COMMENT);
	close(fd);
	return (0);
}
