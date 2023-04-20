/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:27:53 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:24:15 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "vector.h"
#include "miniRT.h"

static t_vec3	determin_sphere(t_sphere *sphere, t_vec3 crosspoint)
{
	t_vec3	normal_vec;

	normal_vec = vec3_normalize(vec3_sub(crosspoint, sphere->center));
	return (normal_vec);
}

static t_vec3	determin_plane(t_plane *plane)
{
	t_vec3	normal_vec;

	normal_vec = plane->normalized;
	return (normal_vec);
}

static t_vec3	determin_cylinder(t_vec3 dir, \
					t_camera *camera, t_cylinder *cylinder, double min)
{
	t_vec3	normal_vec;
	t_vec3	vec_mul;
	t_vec3	tmp_vec;

	tmp_vec = vec3_sub(vec3_add(camera->point, vec3_mul(dir, min)), \
								cylinder->center);
	vec_mul = vec3_mul(cylinder->normalized, \
						vec3_dot(tmp_vec, cylinder->normalized));
	normal_vec = vec3_init(0, 0, 0);
	if (cylinder->front == FRONT || cylinder->front == BACK)
		normal_vec = vec3_normalize(vec3_sub(tmp_vec, vec_mul));
	if (cylinder->front == BACK)
		normal_vec = vec3_mul(normal_vec, -1);
	return (normal_vec);
}

t_vec3	determin(t_rt *rt, t_vec3 crosspoint, t_vec3 dir)
{
	t_vec3		normal_vec;
	t_object	*obj;

	normal_vec = vec3_init(0, 0, 0);
	obj = rt->min_object;
	if (obj->type == SPHERE)
		normal_vec = determin_sphere((t_sphere *)obj->object, crosspoint);
	else if (obj->type == PLANE)
		normal_vec = determin_plane((t_plane *)obj->object);
	else if (obj->type == CYLINDER)
		normal_vec = determin_cylinder(dir, rt->camera, \
					(t_cylinder *)obj->object, rt->min);
	return (normal_vec);
}
