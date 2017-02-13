#include "common.h"

void	write_nb_inst(t_info *info, int fd)
{
	long	i;

	i = 0;
	while (info)
	{
		i += count_byte_inst(info);
		info = info->next;
	}
	i = invert_8(i);
	write(fd, (char*)&i, sizeof(long));
}
