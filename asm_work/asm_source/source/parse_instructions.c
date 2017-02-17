/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/01/18 20:09:40 by rabougue         ###   ########.fr       */
=======
/*   Updated: 2017/02/15 20:11:35 by jcazako          ###   ########.fr       */
>>>>>>> jcazako
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*get_instruction(char *line, bool label_exist)
{
	int	i;

	i = skip_blank(line);
	if (label_exist == true)
	{
		while (line[i] && line[i] != LABEL_END)
			i++;
		if (line[i] == LABEL_END)
			i++;
		if (!line[i])
			return (NULL);
		i += skip_blank(&line[i]);
	}
<<<<<<< HEAD
	label = ft_strndup(&line[skip_blank(line)], count_car_label); // stock le label
	ft_fprintf(1, RED"\nlabel = %s\n"END, label);
	ft_fprintf(1, PURPLE"\nchar =  %c\n"END, label[count_car_label - 1]);
	/*if (ft_strchr(LABEL_CHARS, label[count_car_label -1]) == NULL) */
	if (label[count_car_label -1] == ':') 
		return (label);
	free(label);
	return (0);
=======
	return (&line[i]);
>>>>>>> jcazako
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
<<<<<<< HEAD
	return (true);
}

bool	check_if_instruction_exist(char *instruction)
{
	int		i;
	t_op	op[17];
	uint8_t	len_instruction;

	i = 0;
	len_instruction = skip_blank(&instruction[i]);
	i = 0;
	init_op_table(op);
	while (i < 16)
	{
		if (ft_strncmp(instruction, op[i].instruction_name, len_instruction) == 0)
		{
			free_op_table(op);
			return (true);
		}
		++i;
	}
	free_op_table(op);
	return (false);
=======
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
>>>>>>> jcazako
}

static void	parse_label(t_glob *glob, char *line, bool *label_exist, int i)
{
	char	*label;
	t_label	content;
	t_list	*tmp;

<<<<<<< HEAD
	ft_fprintf(1, "label_exist = %d\n", label_exist);
	i = skip_blank(line); // ignore les espaces
	ft_fprintf(1, ORANGE"line = %s\n"END, line);
	if (label_exist == true) // si il y a un label j'avance jusqua l'instruction
	{
		ft_debug();
		while (line[i] != LABEL_END) // avance jusqu'au ':'
			++i;
		ft_fprintf(1, RED"line = %s\n"END, &line[i]);
			++i; // avance de 1 le curseur (actuellement sur ':')
		if (line[i] == '\0')
			return ;
		i += skip_blank(&line[i]); // ignore les caracteres espaces
		/*ft_fprintf(1, BLUE"line = %s\n"END, &line[i]);*/
		/*if (check_if_instruction_exist(&line[i]) == false) // erreur argument.*/
			/*error(INSTR_INEXIST);*/
=======
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
>>>>>>> jcazako
	}
	ft_fprintf(1, BLUE"line = %s\n"END, &line[i]);
	if (check_if_instruction_exist(&line[i]) == false) // erreur argument.
		error(INSTR_INEXIST);
	(void)label_exist;
}

<<<<<<< HEAD
void	parse_instructions(int *fd)
=======
static void	help(char **line, int label_exist, t_glob *glob, int *i)
{
	char	*tmp;

	if ((tmp = get_instruction(*line, label_exist)) && *tmp)
	{
		if (parse_info(glob, tmp) != TRUE)
		{
			ft_strdel(line);
			error(MALLOC);
		}
		(*i)++;
	}
}

void		parse_instructions(int *fd, t_glob *glob)
>>>>>>> jcazako
{
	char	*line;
	char	*label;
	bool	label_exist;
	int		i;

	label = NULL;
<<<<<<< HEAD
	while (get_next_line(*fd, &line) > 0)
	{
		label_exist = false;
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
=======
	i = 0;
	while (get_next_line(*fd, &line) > 0)
	{
		label_exist = false;
		if (is_cmt(line) == true)
>>>>>>> jcazako
		{
			ft_strdel(&line);
			continue ;
		}
<<<<<<< HEAD
		if ((label = check_if_label_exist(line)) != NULL)
		{
			label_exist = true;
			if (check_if_label_good_formatted(label) == false)
				error(BAD_LABEL_FORMAT);
			free(label);
		}
		// verifier si il y a une instruction apres le label et la parser.
		get_instruction(line, label_exist);
		ft_fprintf(1, YELLOW"line = %s\n"END, line);
		ft_fprintf(1, YELLOW"=================================================\n"END, line);
		ft_strdel(&line);
=======
		else if (ft_strchr(line, '#') || ft_strchr(line, ';'))
			replace_line(&line);
		parse_label(glob, line, &label_exist, i);
		help(&line, label_exist, glob, &i);
		free(line);
>>>>>>> jcazako
	}
}
