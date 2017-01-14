/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/14 21:52:28 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Le terme espace = ' ' et '\t'

#include "common.h"

#define LEN_NAME 5 // taille de .name

static int	check_error_name(char *stock_name)
{
	int		space_before_name;
	int		space_after_name;
	char	after_quote; // stock le caractere apres .name (sauf caractere vide (' ' '\t'))
	int		len_name; // longueur de stock_name
	int		name_start;

	space_before_name = skip_blank(stock_name); // compte le nombre d'espace avant .name
	if (ft_strncmp(&stock_name[space_before_name], ".name", LEN_NAME) != 0)
		error(NAME_NOT_FOUND);
	space_after_name = skip_blank(&stock_name[space_before_name] + LEN_NAME); // compte le nombre d'espace apres .name
	name_start = space_before_name + LEN_NAME + space_after_name + 1; // se place sur le premier caractere du .name
	len_name = ft_strclen(&stock_name[name_start], '"'); // compte le nombre de charactere entre les " de .name
	if (len_name > PROG_NAME_LENGTH) // si la taille du .name est superieur a 128, erreur
		error(LONG_NAME);
	after_quote = stock_name[(name_start + len_name + 1) + skip_blank(&stock_name[(name_start + len_name + 1)])]; // +1 pour skip le dernier '"'
	if (after_quote != COMMENT_CHAR_CROMA && after_quote != COMMENT_CHAR && after_quote != '\0') // verfie si apres la derniere '"' il y a un autre caractere qu'un commentaire.
		error(BAD_FORMAT);
	return (space_before_name + LEN_NAME + space_after_name);
}

// La fonction parse_name sert a verifier puis ecrire le le nom du programme dans le .cor
void	parse_name(int *fd, t_header *header)
{
	char	*line; // stock ce que lis gnl
	char	*stock_name; // stock la ligne de .name
	int		start_name;

	line = NULL;
	stock_name = NULL;
	while (get_next_line(*fd, &line) > 0) // premiere lecture avec gnl
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		stock_name = ft_strjoin(stock_name, line); // concatene ligne
		if (ft_count_char(stock_name, '\"') >= 2) // stop gnl a partir de la quote fermante de .name
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	start_name = check_error_name(stock_name);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH + 1); // mise a NULL "header->prog_name"
	ft_strccat(header->prog_name, &stock_name[start_name + 1], '\"'); // copie le nom du progamme dans "header->prog_name"
	ft_strdel(&stock_name);
}
