/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:39:06 by tasano            #+#    #+#             */
/*   Updated: 2023/04/20 14:51:30 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"
#include "create_map_errno.h"

static int	check_light(char **argv, t_light *light)
{
	if (check_vec(argv[0]))
		return (L_POINT_ERR);
	if (light->ratio < 0.0 || 1.0 < light->ratio)
		return (L_RATIO_ERR);
	if (check_color(light->color))
		return (L_COLOR_ERR);
	return (0);
}

int	set_light(char **argv, t_rt *rt)
{
	if (rt->light)
		return (L_DUP_ERR);
	if (!argv || !argv[0] || !argv[1] || !argv[2] || argv[3])
		return (L_DIF_ELEM_ERR);
	rt->light = (t_light *)malloc(sizeof(t_light));
	if (!rt->light)
		return (MALLOC_ERR);
	rt->light->point = set_vec3(argv[0]);
	rt->light->ratio = ft_atof(argv[1]);
	rt->light->color = set_color(argv[2]);
	return (check_light(argv, rt->light));
}
