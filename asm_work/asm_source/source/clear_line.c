/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:52:19 by jcazako           #+#    #+#             */
/*   Updated: 2017/01/30 17:01:12 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

// remplace les series de tab et de space par UN unique tab ou UN unique space renvoie la string correspondante

static int	gt_wordlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str && !ft_strchr(" \t", *str))
	{
		i++;
		str++;
	}
	return (i);
}

static int	get_len(char *str, int nb)
{
	int		len;

	len = 0;
	while (str && *str)
	{
		if (!ft_strchr(" \t", *str))
			nb++;
		str++;
	}
	return (len + nb - 1);
}

char	*clear_line(char *str)
{
	int		len;
	char	*new;
	int		nb_word;
	int		i;

	nb_word = wordnb(str);
	len = get_len(str, nb_word);
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (nb_word)
	{
		while (str && *str && ft_strchr(" \t", *str))
			str++;
		if (*str)
			ft_strncat(new, str, gt_wordlen(str));
		str += gt_wordlen(str);
		nb_word--;
		if (nb_word)
			ft_strcat(new, " ");
	}
	return (new);
}
