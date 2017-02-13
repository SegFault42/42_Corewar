/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 22:37:34 by jcazako           #+#    #+#             */
/*   Updated: 2017/02/13 22:58:46 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

char	*check_if_label_exist(char *line)
{
	int		i;
	int		count_car_label;
	char	*label;

	i = skip_blank(line);
	count_car_label = 0;
	label = NULL;
	while (line[i] != '\0' && ft_isspace(line[i]) == false)
	{
		++count_car_label;
		++i;
	}
	label = ft_strndup(&line[skip_blank(line)], count_car_label);
	if (label[count_car_label - 1] == ':')
		return (label);
	free(label);
	return (0);
}

bool	check_if_label_good_formatted(char *label)
{
	int	i;
	int	len_label;

	i = 0;
	len_label = ft_strlen(label);
	if (label[len_label - 1] != ':')
		return (false);
	while (i < len_label - 1)
	{
		if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			return (false);
		++i;
	}
	return (true);
}

bool	check_if_instruction_exist(char *instruction)
{
	int		i;
	int		j;

	i = 0;
	j = skip_blank(&instruction[i]);
	while (g_op_tab[i].instruction_name)
	{
		if (!ft_strncmp(&instruction[j],\
			g_op_tab[i].instruction_name,\
			ft_strlen(g_op_tab[i].instruction_name)))
			return (true);
		i++;
	}
	return (false);
}
