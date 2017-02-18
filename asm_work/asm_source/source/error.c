/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 19:14:34 by jcazako           #+#    #+#             */
/*   Updated: 2017/02/18 18:29:42 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	error_2(int error)
{
	if (error == BAD_ARGUMENT)
		ft_fprintf(2, RED"Wrong parametres\n"END);
	else if (error == BAD_NUMBER_PARAM)
		ft_fprintf(2, RED"Wrong number argument in instruction\n"END);
	else if (error == MALLOC)
		ft_fprintf(2, RED"malloc error\n"END);
	else if (error == BAD_FILE)
		ft_fprintf(2, RED"wrong file\n"END);
	else if (error == BAD_COMMENT)
		ft_fprintf(2, RED"./comment bad formatted\n"END);
	else if (error == BAD_NAME)
		ft_fprintf(2, RED"./name bad formatted\n"END);
	else if (error == NO_INSTRUCTION)
		ft_fprintf(2, RED"instruction not found\n"END);
	else
		ft_fprintf(2, RED"Error %d\n"END, error);
}

void	error(int error)
{
	if (error == LONG_NAME)
		ft_fprintf(2, RED"Champion name too long (Max length 128)\n"END);
	else if (error == LONG_COMMENT)
		ft_fprintf(2, RED"Champion comment too long (Max length 2048)\n"END);
	else if (error == CREATING_FILE_ERROR)
		ft_fprintf(2, RED"Creating file error.\n"END);
	else if (error == ERROR_QUOTE)
		ft_fprintf(2, RED"Too many '\"' in .name (Only 2 needed).\n"END);
	else if (error == BAD_FORMAT)
		ft_fprintf(2, RED"Bad format\n"END);
	else if (error == BAD_CHARACTERE)
		ft_fprintf(2, RED"Bad caractere\n"END);
	else if (error == BAD_LABEL_FORMAT)
		ft_fprintf(2, RED"Error label bad formatted.\nAllowed caractere\
		: digit (0-9) alpha, (a-z) and underscore ('_').\n"END);
	else if (error == NAME_NOT_FOUND)
		ft_fprintf(2, RED".name missing\n"END);
	else if (error == COMMENT_NOT_FOUND)
		ft_fprintf(2, RED".comment missing\n"END);
	else if (error == INSTR_INEXIST)
		ft_fprintf(2, RED"Instruction not valid\n"END);
	else
		error_2(error);
	exit(EXIT_FAILURE);
}
