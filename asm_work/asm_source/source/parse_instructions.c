/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/13 16:23:39 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*check_if_label_exist(char *line)
{
	int	i; // variable qui stocke le nombre de caractere d'indentaation.
	int	count_car_instr; // compte le nombre de caractere d'une instruction.
	char	*instr; // stock la premiere chaine de caractere j'usqu'au caractere blanc (' ' ou '\t')

	i = skip_blank(line);
	count_car_instr = 0;
	instr = NULL;
	while (line[i] != '\0' && ft_isspace(line[i]) == false)
	{
		++count_car_instr;
		++i;
	}
	instr = ft_strndup(&line[skip_blank(line)], count_car_instr);
	ft_fprintf(1, PURPLE"\ninstr = %s\n"END, instr);
	ft_fprintf(1, PURPLE"\nchar =  %c\n"END, instr[count_car_instr - 1]);
	if (instr[count_car_instr -1] == ':')
		return (instr);
	return (NULL);
	/*instr = (char *)ft_memalloc(sizeof(char) * count_car_instr);*/

	/*while (line[i] != ':')*/
	/*{*/
		/*if (ft_strchr(LABEL_CHARS, line[i]) == NULL)*/
			/*return (false);*/
		/*++i;*/
	/*}*/
}
bool	check_if_label_good_formatted(char *label)
{
	ft_fprintf(1, "label = %s", label);
	/*int	i;*/

	/*i = 0;*/
	/*while (line[i] != ':')*/
	/*{*/
		/*if (ft_strchr(LABEL_CHARS, line[i]) == NULL)*/
			/*return (false);*/
		/*++i;*/
	/*}*/
	return (false);
}

void	check_label(int *fd)
{
	char	*line;
	char	*label;

	while (get_next_line(*fd, &line) > 0)
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		if ((label = check_if_label_exist(line)) != NULL)
		{
			if (check_if_label_good_formatted(label) == false)
				error(BAD_LABEL_FORMAT);
		}
		ft_fprintf(1, YELLOW"line = %s\n"END, line);
		ft_strdel(&line);
	}
}
