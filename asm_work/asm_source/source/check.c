#include "common.h"
#include "functions.h"

/*static int	check_6(t_info *info)
{
	char	**param;
	int	i;

	param = info->param;
	i = 0;
	
	while (param && param[i])
		i++;
	if (i != (int)g_op_tab[(int)info->opcode - 1].nb_arg)
		return (1);
	return (0);
}

static int	check_5(t_glob glob, t_info *info)
{
	char	**param;
	t_list	*label;

	param = info->param;
	label = glob.label;
	while (param && *param)
	{
		if (is_direct(*param) && ft_strchr(*param, '%')\
			&& ft_strchr(*param, ':'))
		{
			if (!ft_strcmp(*param + 2, ""))
				return (1);
			while (label && ft_strncmp(*param + 2, l_str(label),\
				ft_strlen(*param + 2)))
				label = label->next;
			if (!label)
				return (1);
		}
		param++;
	}
	return (0);
}*/

static int	check_4(t_info *info)
{
	char	**param;

	param = info->param;
	while (param && *param)
	{
		if (!ft_strcmp(*param, ""))
			return (1);
		param++;
	}
	return (0);
}

static int	check_3(t_info *info)
{
	char	**param;

	param = info->param;
	while (param && *param)
	{
		if (!is_reg(*param) && !is_direct(*param) && !is_ind(*param))
			return (1);
		param++;
	}
	return (0);
}

static	int	check_2(t_info *info)
{
	char	**param;
	char	*reg;
	int	tmp;

	param = info->param;
	while (param && *param)
	{
		if (is_reg((reg = *param)))
		{
			while (reg && *reg && ft_strchr(" \t", *reg))
				reg++;
			if (*reg == 'r')
				tmp++;
			if ((tmp = ft_atoi(reg)) > 99 || tmp < 0)
				return (1);
		}
		param++;
	}
	return (0);
}

static int	check_1(t_glob glob)
{
	if (!glob.list)
		return (1);
	return (0);
}

int	check(t_glob glob)
{
	t_info	*info;

	info = glob.list;
	while (info)
	{
		if (check_1(glob))
			return (1);
		else if (check_2(info))
			return (2);
		else if (check_3(info))
			return (3);
		else if (check_4(info))
			return (4);
		else if (check_5(glob, info))
			return (5);
		else if (check_6(info))
			return (6);
		info = info->next;
	}
	return (0);
}
