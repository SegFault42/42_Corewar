#include "common.h"
#include "functions.h"

int	check_6(t_info *info)
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

int	check_5(t_glob glob, t_info *info)
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
}
