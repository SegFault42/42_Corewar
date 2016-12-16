/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 17:30:39 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/16 18:51:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printmem.h"
#include <fcntl.h>

int		ft_error(char *msg, char *str)
{
	if (msg && str)
		ft_printf("%s: %s\n", str, msg);
	else if (msg)
		ft_printf("%s\n", msg);
	return (-1);
}

int 	ft_to_big_endian(int x)
{
	x = ((x >> 8) & 0x00ff00ffu) | ((x & 0x00ff00ffu) << 8);
	x = ((x >> 16) & 0xffffu) | ((x & 0xffffu) << 16);
	return (x);
}

int		ft_readprog(int fd, size_t prog_size, unsigned char *prog_name)
{
	int				ret;
	int				prog[prog_size];

	ft_printf("\nProgram:\n");
	ft_printf("	size: %x\n", prog_size);
	ft_printf("	name: %s\n", prog_name);
	if ((ret = read(fd, prog, prog_size)))
	{
		print_memory(prog, prog_size);
	}
	return (0);
}

unsigned char	*ft_ustrndup(unsigned char *str, size_t size)
{
	unsigned char	*dup;
	size_t			i;

	i = -1;
	if ((dup = malloc(sizeof(*dup) * size)) == NULL)
		return (NULL);
	while (++i < size && str[i])
	{
		dup[i] = str[i];
	}
	dup[i] = '\0';
	return (dup);
}

int		ft_readfile(int fd)
{
	int				ret;
	int				head[HEAD_SIZE];
	int				prog_size;
	unsigned char	*prog_name;

	prog_size = 0;
	prog_name = NULL;
	if ((ret = read(fd, head, HEAD_SIZE)))
	{
		if (ft_to_big_endian(head[0]) == MAGIC_N)
		{
			print_memory(head, HEAD_SIZE);
			prog_size = ft_to_big_endian(head[34]);
			prog_name = ft_ustrndup((unsigned char*)&head[1], 128);
		}
		else
			return (ft_error("Not a corewar program.", NULL));
	}
	return (ft_readprog(fd, prog_size, prog_name));
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) > 0)
		{
			read(1, NULL, 0);
			ft_readfile(fd);
			if (close(fd))
				ft_error("Failed to close fd", NULL);
		}
		else
			ft_error("Failed opening file", NULL);
	}
	else
		ft_error("Not enough arguments", NULL);
	return (0);
}
