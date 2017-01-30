/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/30 17:35:47 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	is_cmt(char *line)
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

//retourne le nombre de mot dans une string

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
