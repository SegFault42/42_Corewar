/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/30 16:12:13 by jcazako          ###   ########.fr       */
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
	free(label);
	return (0);
}

bool	check_if_label_good_formatted(char *label)
{
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

bool	check_if_instruction_exist(char *instruction)
{
	int		i;
	int		j;
	t_op	op[17];

	i = 0;
	j = skip_blank(&instruction[i]);
	init_op_table(op);
	while (i < 16)
	{
		if (ft_strncmp(&instruction[j], op[i].instruction_name,
				ft_strlen(op[i].instruction_name)) == 0)
		{
			free_op_table(op);
			return (true);
		}
		++i;
	}
	free_op_table(op);
	return (false);
}

char	*get_instruction(char *line, bool label_exist)
{
	int	i;

	i = skip_blank(line); // ignore les espaces
	if (label_exist == true) // si il y a un label j'avance jusqua l'instruction
	{
		while (line[i] != LABEL_END) // avance jusqu'au ':'
			++i;
		++i; // avance de 1 le curseur (actuellement sur ':')
		if (line[i] == '\0')
			return NULL;
		i += skip_blank(&line[i]); // ignore les caracteres espaces
	}
	if (check_if_instruction_exist(&line[i]) == false) // erreur argument.
		error(INSTR_INEXIST);
	return (&line[i]);
}

static void	replace_line(char **line)
{
	char	*tmp;

	tmp = *line;
	if (ft_strchr(*line, ';') && !ft_strchr(*line, '#'))
	{
		*line = ft_strsub(*line, 0, ft_strchr(*line, ';') - *line);
		ft_strdel(&tmp);
	}
	else if (!ft_strchr(*line, ';') && ft_strchr(*line, '#'))
	{
		*line = ft_strsub(*line, 0, ft_strchr(*line, '#') - *line);
		ft_strdel(&tmp);
	}
	else if (ft_strchr(*line, ';') && ft_strchr(*line, '#'))
	{
		if (ft_strchr(*line, ';') > ft_strchr(*line, '#'))
			*line = ft_strsub(*line, 0, ft_strchr(*line, '#') - *line);
		else
			*line = ft_strsub(*line, 0, ft_strchr(*line, ';') - *line);
		ft_strdel(&tmp);
	}	
}

static void	parse_label(t_glob *glob, char *line, bool *label_exist, int i)
{
	char	*label;
	t_label	content;
	t_list	*tmp;

	if ((label = check_if_label_exist(line)))
	{
		*label_exist = true;
		if (check_if_label_good_formatted(label) == false)
			error(BAD_LABEL_FORMAT);
		content.str = label;
		content.n_inst = i;
		if (!(tmp = ft_lstnew(&content, sizeof(content))))
			error(MALLOC);
		ft_lstadd(&glob->label, tmp);
		//free(label);
	}
}

void	parse_instructions(int *fd, t_glob *glob)
{
	char	*line;
	char	*label;
	bool	label_exist;
	int	parse;
	int	i;

	label = NULL;
	i = 0;
	while (get_next_line(*fd, &line) > 0)
	{
		label_exist = false;
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		else if (ft_strchr(line, '#') || ft_strchr(line, ';'))
			replace_line(&line);
		parse_label(glob, line, &label_exist, i);
		line = get_instruction(line, label_exist);
		if (line)
		{
			if ((parse = parse_info(glob, line)) != TRUE)
			{
				ft_strdel(&line);
				error(parse);
			}
			i++;
		}
	}
}
