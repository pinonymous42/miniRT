/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixcel_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:31:14 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:00:36 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "miniRT.h"
#include "draw.h"

int	check_distance(t_vec3 crosspoint_vec, t_vec3 incident_vec, double shadow, t_vec3 light_point)
{
	double distance;

	distance = vec3_mag(vec3_sub(light_point, crosspoint_vec)) - EPSILON;
	return (distance < vec3_mag(vec3_add(crosspoint_vec, vec3_mul(incident_vec, EPSILON + shadow))));
}

t_fcolor	get_pixcel_color(t_object *min_object, double min, t_rt *rt, double shadow, t_vec3 dir_vec)
{
	t_fcolor color;
	t_vec3 reflect_normal_vec;
	t_vec3 crosspoint_vec;
	t_vec3 incident_vec;

	if (min <= 0)
		return (rgb_init(255, 255, 255));
	color = rgb_init(0, 0, 0);
	color = add_color(color, rt->ambient->color, rt->ambient->ratio);
	crosspoint_vec = get_crosspoint_vec(rt->camera->point, dir_vec, min);
	incident_vec = get_incident_vec(rt->light->point, crosspoint_vec);
	if (shadow == 0 || check_distance(crosspoint_vec, incident_vec, shadow, rt->light->point))
	{
		reflect_normal_vec = determin_normal_vec(rt, min_object, crosspoint_vec, dir_vec, min);
		color = diffusion(incident_vec, reflect_normal_vec, min_object, color);
		color = specular(dir_vec, reflect_normal_vec, incident_vec, color, rt->light->color, rt->light->ratio);
	}
	return (color);
}