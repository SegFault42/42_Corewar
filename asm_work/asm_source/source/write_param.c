#include "common.h"
#include "functions.h"

/*static void aff_param(char **param)
{
	while (param && *param)
	{
		ft_putstr(*param++);
		if (*param)
			ft_putchar(' ');
	}
	ft_putchar('\n');
}*/

void	write_reg(int fd, int i, t_info *info)
{
	int	tmp;
	char	*reg;

	reg = info->param[i];
	reg++;
	tmp = 0;
	tmp = ft_atoi(reg);
	write(fd, (char*)&tmp, T_REG);
}

void	write_dir(int fd, int i, t_info *info, t_glob glob)
{
	int	tmp;
	char	opcode;
	
	opcode = info->opcode;
	//if (g_op_tab[opcode - 1].dir_indir)
	if (opcode == ZJUMP || opcode == LDI || opcode == STI \
		|| opcode == FORK || opcode == LLDI || opcode == LFORK)
	{
		//ft_putendl("A");
		//ft_putendl(info->param[i]);
		if (!ft_strchr(info->param[i], (int)':'))
		{
			//ft_putstr("C");
			tmp = ft_atoi(info->param[i] + 1);
			tmp = invert_2(tmp);
			//ft_putnbr(tmp);
			//ft_putchar('\n');
			
		}
		else
		{
			//ft_putstr("D");
			tmp = get_label_val(info, glob, i);
			tmp = invert_2(tmp);
			//ft_putnbr(tmp);
			//ft_putchar('\n');
		}
		write(fd, (char*)&tmp, T_DIR);
	}
	else
	{
		//ft_putendl("B");
		//ft_putendl(info->param[i]);
		if (!ft_strchr(info->param[i], (int)':'))
		{
			//ft_putstr("E");
			tmp = ft_atoi(info->param[i] + 1);
			tmp = invert_4(tmp);
			//ft_putnbr(tmp);
			//ft_putchar('\n');
		}
		else
		{
			//ft_putstr("F");
			tmp = get_label_val(info, glob, i);
			tmp = invert_4(tmp);
			//ft_putnbr(tmp);
			//ft_putchar('\n');
		}
		write(fd, (char*)&tmp, T_IND);
	}
}

void	write_ind(int fd, int i, t_info *info, t_glob glob)
{
	int	tmp;

	if (!ft_strchr(info->param[i], (int)':'))
		tmp = ft_atoi(info->param[i]);
	else
		tmp = get_label_val(info, glob, i);
	tmp = invert_2(tmp);
	write(fd, (char*)&tmp, T_DIR);
}

static void	w_param(int fd, t_info *info, t_glob glob)
{
	char	**param;
	int	i;
	char	opcode;

	param = info->param;
	i = 0;
	opcode = info->opcode;
	while (param && *param)
	{
		if (is_reg(*param))
			write_reg(fd, i, info);
		else if (is_direct(*param))
			write_dir(fd, i, info, glob);
		else if (is_ind(*param))
			write_ind(fd, i, info, glob);
		/*else
		{
			ft_putstr("PWOBLEM type arg: ");
			ft_putendl(*param);
		}*/
		i++;
		param++;
	}
}

static void	deal_param(int fd, t_info *info, t_glob glob)
{
	t_op	op[17];
	char	*opcode;
	char	*ocp;

	opcode = &info->opcode;
	ocp = (char*)&info->ocp;
	init_op_table(op);
	write(fd, opcode, 1);
	if (*opcode != LIVE && *opcode != ZJUMP && *opcode != FORK)
		write(fd, ocp, 1);
	w_param(fd, info, glob);
	free_op_table(op);
}

void		write_param(int fd, t_glob glob)
{
	t_info	*info;

	info = glob.list;
	while (info)
	{
		deal_param(fd, info, glob);
		info = info->next;
	}
}
