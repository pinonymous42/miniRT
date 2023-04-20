/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixcel_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:31:14 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 22:17:52 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "miniRT.h"
#include "draw.h"
#include "material.h"

static int	check_distance(t_vec3 crosspoint, t_vec3 incident, \
					double shadow, t_rt *rt)
{
	double	distance;

	distance = vec3_mag(vec3_sub(rt->light->point, crosspoint)) - rt->epsilon;
	return (shadow == 0 || distance < vec3_mag(vec3_add(crosspoint, \
			vec3_mul(incident, rt->epsilon + shadow))));
}

static t_fcolor	get_object_color(t_object *object)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cilinder;

	if (object->type == SPHERE)
	{
		sphere = object->object;
		return (sphere->color);
	}
	else if (object->type == PLANE)
	{
		plane = object->object;
		return (plane->color);
	}
	else if (object->type == CYLINDER)
	{
		cilinder = object->object;
		return (cilinder->color);
	}
	return (rgb_init(255, 255, 255));
}

static t_fcolor	set_color(t_material_val val, t_fcolor color, t_rt *rt)
{
	t_fcolor	obj_color;

	obj_color = get_object_color(rt->min_object);
	color = add_color(color, obj_color, val.diffusion);
	color = add_color(color, rt->light->color, rt->light->ratio * val.speclar);
	return (color);
}

t_fcolor	get_pixcel_color(t_rt *rt, double shadow, t_vec3 dir_vec)
{
	t_fcolor		color;
	t_vec3			reflect_normal_vec;
	t_vec3			crosspoint;
	t_vec3			incident;
	t_material_val	val;

	if (rt->min <= 0)
		return (rgb_init(255, 255, 255));
	color = add_color(rgb_init(0, 0, 0), \
			rt->ambient->color, rt->ambient->ratio);
	crosspoint = get_crosspoint_vec(rt->camera->point, dir_vec, rt->min);
	incident = get_incident_vec(rt->light->point, crosspoint);
	if (check_distance(crosspoint, incident, shadow, rt))
	{
		reflect_normal_vec = determin(rt, crosspoint, dir_vec, rt->min);
		val.diffusion = diffusion(incident, reflect_normal_vec);
		val.speclar = specular(dir_vec, reflect_normal_vec, incident);
		color = set_color(val, color, rt);
	}
	return (color);
}
