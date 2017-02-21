/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 10:45:26 by hboudra           #+#    #+#             */
/*   Updated: 2017/02/21 15:04:29 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

/*
** la fonction is_reg sert à checker si str est un registre, renvoi 1 si oui
** 0 dans le cas contraire. il faut lui passer une chaine contenant uniquement
** le parametre de l'instruction ex: "		r1",  "r1".
** si il y a des caracteres à la fin elle renverra false.
*/

int		is_reg(char *str)
{
	while (str && *str && ft_strchr(" \t", *str))
		str++;
	if (str && *str == 'r')
	{
		str++;
		while (*str && ft_isdigit(*str))
			str++;
		if (!*str)
			return (TRUE);
	}
	return (FALSE);
}

/*
** la fonction is_direct sert à checker si str est une direct, renvoi 1 si oui
** 0 dans le cas contraire. il faut lui passer une chaine contenant uniquement
** le parametre de l'instruction ex: "		%123",  "%1231".
** si il y a des caracteres à la fin elle renverra false.
*/

int		is_direct(char *str)
{
	while (str && *str && ft_strchr(" \t", *str))
		str++;
	if (str && *str == DIRECT_CHAR && *(str + 1) == LABEL_END)
	{
		str += 2;
		while (*str && ft_strchr(LABEL_CHARS, *str))
			str++;
		if (!*str)
			return (TRUE);
	}
	else if (str && *str == DIRECT_CHAR
		&& (*(str + 1) == '-' || ft_isdigit(*(str + 1))))
	{
		str = (*(str + 1) == '-') ? str + 2 : str + 1;
		while (*str && ft_isdigit(*str))
			str++;
		if (!*str)
			return (TRUE);
	}
	return (FALSE);
}

/*
** la fonction is_reg sert à checker si str est un registre, renvoi 1 si oui
** 0 dans le cas contraire. il faut lui passer une chaine contenant uniquement
** le parametre de l'instruction ex: "		label",  "123".
** si il y a des caracteres à la fin elle renverra false.
*/

int		is_ind(char *str)
{
	while (str && *str && ft_strchr(" \t", *str))
		str++;
	if (str && *str == LABEL_END)
	{
		str++;
		while (*str && ft_strchr(LABEL_CHARS, *str))
			str++;
		if (!*str)
			return (TRUE);
	}
	else if (str)
	{
		if (*str == '-')
			str++;
		while (*str && ft_isdigit(*str))
			str++;
		if (!*str)
			return (TRUE);
	}
	return (FALSE);
}
