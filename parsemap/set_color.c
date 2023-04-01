/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:24 by tasano            #+#    #+#             */
/*   Updated: 2023/03/31 20:40:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color set_color(char *arg)
{
	char **tmp;
	t_color res;

	tmp = ft_split(arg, ',');
	if (tmp && tmp[0])
		res.r = ft_atoi(tmp[0]);
	else
		res.r = 0;
	if (tmp && tmp[1])
		res.g = ft_atoi(tmp[1]);
	else
		res.g = 0;
	if (tmp && tmp[2])
		res.b = ft_atoi(tmp[2]);
	else
		res.b = 0;
	free_args(tmp);
	return (res);
}
