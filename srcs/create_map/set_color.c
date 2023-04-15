/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:24 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 00:49:36 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"
#include "util.h"

int check_color(t_fcolor color)
{
	if (color.red < 0 || 255 < color.red)
		return (1);
	if (color.green < 0 || 255 < color.green)
		return (1);
	if (color.blue < 0 || 255 < color.blue)
		return (1);
	return (0);
}

t_fcolor set_color(char *arg)
{
	char **tmp;
	t_fcolor res;

	tmp = ft_split(arg, ',');
	res = rgb_init(-1, -1, -1);
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		return res;
	}
	res = rgb_init(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	free_args(tmp);
	return (res);
}
