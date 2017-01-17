/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 10:45:26 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/17 17:31:01 by hboudra          ###   ########.fr       */
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
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'r')
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
		if (!str[i])
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
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '%')
	{
		i++;
		if (str[i] == ':')
			i++;
		while (ft_strchr(LABEL_CHARS, str[i]))
			i++;
		if (!str[i])
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
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (ft_strchr(LABEL_CHARS, str[i]))
	{
		i += 2;
		while (ft_strchr(LABEL_CHARS, str[i]) && str[i])
			i++;
		if (!str[i])
			return (TRUE);
	}
	return (FALSE);
}
