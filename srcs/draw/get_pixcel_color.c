/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixcel_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:31:14 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 18:20:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"


#include <stdio.h>


#include "miniRT.h"
#include "draw.h"

int	check_distance(t_vec3 crosspoint, t_vec3 incident, double shadow, t_vec3 light_point)
{
	double distance;

	distance = vec3_mag(vec3_sub(light_point, crosspoint)) - EPSILON;
	return (distance < vec3_mag(vec3_add(crosspoint, vec3_mul(incident, EPSILON + shadow))));
}

t_fcolor	get_pixcel_color(t_rt *rt, double shadow, t_vec3 dir_vec)
{
	t_fcolor color;
	t_vec3 reflect_normal_vec;
	t_vec3 crosspoint;
	t_vec3 incident;

	if (rt->min <= 0)
		return (rgb_init(255, 255, 255));
	color = rgb_init(0, 0, 0);
	color = add_color(color, rt->ambient->color, rt->ambient->ratio);
	crosspoint = get_crosspoint_vec(rt->camera->point, dir_vec, rt->min);
	incident = get_incident_vec(rt->light->point, crosspoint);
	if (shadow == 0 || check_distance(crosspoint, incident, shadow, rt->light->point))
	{
		reflect_normal_vec = determin(rt, crosspoint, dir_vec, rt->min);;
		color = diffusion(incident, reflect_normal_vec, rt->min_object, color);
		color = specular(dir_vec, reflect_normal_vec, incident, color, rt->light->color, rt->light->ratio);
	}
	return (color);
}