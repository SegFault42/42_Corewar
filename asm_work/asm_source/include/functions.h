/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:10:28 by hboudra           #+#    #+#             */
/*   Updated: 2017/01/19 14:35:12 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
#define FUNCTION_H

int					is_reg(char *str);
int					is_direct(char *str);
int					is_ind(char *str);
unsigned char		ocp_calc(char **tab);

#endif
