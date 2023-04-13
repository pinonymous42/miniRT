/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determin_normal_vec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:27:53 by tasano            #+#    #+#             */
/*   Updated: 2023/04/13 23:25:13 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "vector.h"
#include "miniRT.h"

t_vec3 determin_normal_vec_sphere(t_sphere *sphere, t_vec3 crosspoint_vec)
{
	t_vec3 normal_vec;

	normal_vec = vec3_normalize(vec3_sub(crosspoint_vec, sphere->center)); // 法線ベクトル
	return (normal_vec);
}

t_vec3 determin_normal_vec_plane(t_plane *plane)
{
	t_vec3 normal_vec;

	normal_vec = plane->normalized; // 法線ベクトル
	return (normal_vec);
}

t_vec3 determin_normal_vec_cylinder(t_vec3 dir_vec, t_camera *camera, t_cylinder *cylinder, double t)
{
	t_vec3 normal_vec;

	t_vec3 tmp_vec = vec3_sub(vec3_add(camera->point, vec3_mul(dir_vec, t)), cylinder->center);
	normal_vec = vec3_init(0, 0, 0);
	if (cylinder->front == FRONT)
		normal_vec = vec3_normalize(vec3_sub(tmp_vec, vec3_mul(cylinder->normalized, vec3_dot(tmp_vec, cylinder->normalized))));
	else if (cylinder->front == BACK)
		normal_vec = vec3_mul(vec3_normalize(vec3_sub(tmp_vec, vec3_mul(cylinder->normalized, vec3_dot(tmp_vec, cylinder->normalized)))), -1);
	return (normal_vec);
}

t_vec3 determin_normal_vec(t_rt *rt, t_object *object, t_vec3 crosspoint_vec, t_vec3 dir_vec, double min)
{
	t_vec3 normal_vec = vec3_init(0, 0, 0);
	
	if (object->type == SPHERE)
		normal_vec = determin_normal_vec_sphere((t_sphere *)object->object, crosspoint_vec);
	else if (object->type == PLANE)
		normal_vec = determin_normal_vec_plane((t_plane *)object->object);
	else if (object->type == CYLINDER)
		normal_vec = determin_normal_vec_cylinder(dir_vec, rt->camera, (t_cylinder *)object->object, min);
	return (normal_vec);
}
