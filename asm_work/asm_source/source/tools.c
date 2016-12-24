/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:53:07 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/19 17:58:50 by rabougue         ###   ########.fr       */
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
