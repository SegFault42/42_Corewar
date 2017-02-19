/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <rabougue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/18 22:04:45 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	clear_label(t_glob *glob)
{
	t_list	*label;

	label = glob->label;
	while (label)
	{
		*ft_strchr(l_str(label), ':') = '\0';
		label = label->next;
	}
}

int8_t	parse_s_file(char *file, t_header *header, t_glob *glob)
{
	int	fd;

	if ((fd = open(file, O_RDWR)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	parse_comment(&fd, header);
	parse_instructions(&fd, glob);
	clear_label(glob);
	return (EXIT_SUCCESS);
}
