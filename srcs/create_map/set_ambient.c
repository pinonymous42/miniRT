/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:44 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 15:06:16 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"
#include "miniRT.h"

static int check_ambient(t_ambient *ambient)
{
	if (ambient->ratio < 0 || 1 < ambient->ratio)
		return (1);
	if (check_color(ambient->color))
		return (1);
	return (0);
}

int set_ambient(char **argv, t_rt *rt)
{
	if (!argv || !argv[0] || !argv[1])
		return (1);
	rt->ambient.ratio = ft_atof(argv[0]);
	rt->ambient.color = set_color(argv[1]);
	if (check_ambient(&rt->ambient))
		return (1);
	return (0);
}
