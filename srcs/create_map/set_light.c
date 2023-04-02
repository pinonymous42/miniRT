/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:39:06 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 08:56:24 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"

static int check_light (char **argv, t_light *light)
{
	if (check_vec(argv[0]))	
		return (1);
	if (light->ratio < 0.0 || 1.0 < light->ratio)
		return (1);
	if (check_color(light->color))
		return (1);
	return (0);
}

int set_light(char **argv, t_rt *rt)
{
	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (1);
	rt->light = (t_light *)malloc(sizeof(t_light));
	if (!rt->light)
		return (1);
	rt->light->point = set_vec3(argv[0]);
	rt->light->ratio = ft_atof(argv[1]);
	rt->light->color = set_color(argv[2]);
	if (check_light(argv, rt->light))
		return (1);
	return (0);
}