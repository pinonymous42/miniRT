/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:40:42 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 18:48:24 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "vector.h"
#include "object.h"
#include "material.h"

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

static double	get_diffusion(t_vec3 incident, t_vec3 reflect)
{
	double	dot_1;

	dot_1 = vec3_dot(incident, reflect);
	if (dot_1 <= 0)
		dot_1 = 0;
	return (dot_1 * KDIF);
}

t_fcolor	diffusion(t_vec3 incident, t_vec3 reflect, \
						t_object *object, t_fcolor new)
{
	double		diffusion;
	t_fcolor	color;

	color = get_object_color(object);
	diffusion = get_diffusion(incident, reflect);
	return (add_color(new, color, diffusion));
}
