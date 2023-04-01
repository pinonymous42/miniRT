/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:24 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 17:42:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color set_color(char *arg)
{
	char **tmp;
	t_color res;

	tmp = ft_split(arg, ',');
	res.r = -1;
	res.g = -1;
	res.b = -1;
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		return res;
	}
	res.r = ft_atoi(tmp[0]);
	res.g = ft_atoi(tmp[1]);
	res.b = ft_atoi(tmp[2]);
	free_args(tmp);
	return (res);
}
