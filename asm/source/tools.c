/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/15 22:41:50 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		is_cmt(char *line)
{
	int	blank;

	blank = skip_blank(line);
	if (line[blank] == COMMENT_CHAR ||
		line[blank] == '\0' ||
		line[blank] == COMMENT_CHAR_CROMA)
		return (true);
	return (false);
}

int		skip_blank(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) == true)
		++i;
	return (i);
}

/*
** retourne le nombre de mot dans une string
*/

int		wordnb(char *str)
{
	int	nb;

	nb = 0;
	if (!str)
		return (0);
	while (*str)
	{
		while (*str && ft_strchr(" \t", *str))
			str++;
		if (*str)
		{
			nb++;
			while (*str && !ft_strchr(" \t", *str))
				str++;
		}
	}
	return (nb);
}

long	get_nbr(const char *str)
{
	long	nb;
	long	signe;
	int		len;

	nb = 0;
	signe = 1;
	while (str && *str && ft_strchr(" \t\n\v\r\f", *str))
		str++;
	if (str && *str == '-')
	{
		signe = -1;
		str++;
	}
	if ((len = ft_strlen(str)) > (int)ft_strlen(MAX_LONG) && signe == 1)
		return (LONG_MAX);
	else if (len > (int)ft_strlen(MAX_LONG) && signe == -1)
		return (0);
	while (str && ft_isdigit(*str))
		nb = nb * 10 + *str++ - '0';
	if (len == (int)ft_strlen(MAX_LONG) && nb < 0 && signe == 1)
		return (LONG_MAX);
	else if (len == (int)ft_strlen(MAX_LONG) && nb < 0 && signe == -1)
		return (0);
	return (nb * signe);
}
