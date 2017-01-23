/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/17 21:10:06 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*check_if_label_exist(char *line)
{
	int		i; // variable qui stocke le nombre de caractere d'indentation.
	int		count_car_label; // compte le nombre de caractere d'une label.
	char	*label; // stock la premiere chaine de caractere j'usqu'au caractere blanc (' ' ou '\t')

	i = skip_blank(line); // skip les espaces
	count_car_label = 0;
	label = NULL;
	while (line[i] != '\0' && ft_isspace(line[i]) == false) // boucle jusqua la fin du label
	{
		++count_car_label;
		++i;
	}
	label = ft_strndup(&line[skip_blank(line)], count_car_label); // stock le label
	if (label[count_car_label -1] == ':') 
		return (label);
	return (NULL);
}

bool	check_if_label_good_formatted(char *label)
{
	//ft_fprintf(1, "label = %s\n", label);
	int	i;
	int	len_label; // longeur du label

	i = 0;
	len_label = ft_strlen(label);
	if (label[len_label -1] != ':') // si le dernier caractere du label est != de ':' alors error
		return (false);
	while (i < len_label -1) // verification que le label contient que des caracteres autorise
	{
		if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			return (false);
		++i;
	}
	return (true);
}

void	check_if_instruction_exist(char *instr)
{
	int	i;
	t_op	op[17];

	i = 0;
	init_op_table(op);
	while (i < 16)
	{
		if (!ft_strncmp(instr, op[i].instruction_name, ft_strclen(instr, ' ')))
		{
			//printf(YELLOW"op->instruction_name = %s\n"END, op[i].instruction_name);
			break;
		}
		else if (i == 15)
			error(BAD_INST);
		++i;
	}
	free_op_table(op);
}

static int	get_param(int pos, char *line)
{
	int	i;
	char	*str;
	int	len;

	i = 0;
	str = NULL;
	len = ft_strlen(line);
	while (line[pos + i] && ft_strchr(" /t", line[pos + i]))
		i++;
	if (line[pos + i])
		if (!(str = ft_strsub(line, pos + i, len - pos - i)))
			return (-1);
	ft_fprintf(1, "%s\n", str);
	return (i);
}

int	get_instruction(char *line, bool label_exist)
{
	int	i;

	i = 0;
	i = skip_blank(line); // ignore les espaces
	if (label_exist == true) // si il y a un label j'avance jusqua l'instruction
	{
		while (line[i] != LABEL_END) // avance jusqu'au ':'
			++i;
		++i; // avance de 1 le curseur (actuellement sur ':')
		if (line[i] == '\0')
			return (0);
		i += skip_blank(&line[i]); // ignore les caracteres espaces
		check_if_instruction_exist(&line[i]);
	}
	else
		check_if_instruction_exist(&line[i]);
	while (line[i] && !ft_strchr(" \t", line[i]))
		i++;
	return (i);
}

void	parse_instructions(int *fd)
{
	char	*line;
	char	*label;
	bool	label_exist;
	int	i;

	while (get_next_line(*fd, &line) > 0)
	{
		i = 0;
		label_exist = false;
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		if ((label = check_if_label_exist(line)) != NULL)
		{
			label_exist = true;
			if (check_if_label_good_formatted(label) == false)
				error(BAD_LABEL_FORMAT);
		}
		// verifier si il y a une instruction apres le label et la parser.
		i = get_instruction(line, label_exist);
		get_param(i, line);
		//ft_fprintf(1, YELLOW"line = %s\n"END, line);
		//ft_fprintf(1, YELLOW"=================================================\n"END);
		ft_strdel(&line);
	}
}
