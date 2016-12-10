#include "./libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define MAGIC 0xea83f3


int	main(int argc, char **argv)
{
	char	*file;
	int		fd;

	if (argc != 2)
		exit(-1);
	file = (char *)ft_memalloc(sizeof(char) * (ft_strlen(argv[1])) + 2);
	//Alloc len (name of the output.s + len .cor - ".c")
	ft_strccat(file, argv[1], '.');
	ft_strcat(file, ".cor");
	if((fd = creat(file, S_IRWXU)) < 0)
	{
		ft_fprintf(2, RED"Creating file error.\n"END);
		return (EXIT_FAILURE);
	}
	fd = open(file, O_RDWR);
	ft_fprintf(fd, "%d", MAGIC);
	close(fd);
	return (0);
}
