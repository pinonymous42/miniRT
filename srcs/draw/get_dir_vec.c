/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_vec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:43:04 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 19:01:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "miniRT.h"
#include "mlx_info.h"
#include "dir_vec.h"
#include <math.h>

static int	check_vertical(t_vec3 normal_vec)
{
	if (normal_vec.x == 0 && \
		(normal_vec.y == 1 || normal_vec.y == -1) && \
		normal_vec.z == 0)
		return (1);
	return (0);
}

t_orthonormal	init_unit(t_vec3 camera_normal_vec)
{
	t_orthonormal	ret;
	t_vec3			y_unit_vector;

	if (check_vertical(camera_normal_vec) == 1)
		y_unit_vector = vec3_init(1, 0, 0);
	else
		y_unit_vector = vec3_init(0, 1, 0);
	ret.x_unit_vector = vec3_cross(y_unit_vector, camera_normal_vec);
	ret.y_unit_vector = vec3_cross(camera_normal_vec, ret.x_unit_vector);
	return (ret);
}

t_vec3	get_dir_vec(double x, double y, t_rt *rt)
{
	t_vec3			screen_vec;
	t_orthonormal	screen_unit_vec;
	double			f_x;
	double			f_y;
	double			camera2screen;

	screen_unit_vec = init_unit(rt->camera->normalized);
	camera2screen = 2 / (2 * tan(((rt->camera->fov / 180 * M_PI) / 2)));
	f_x = 2 * x / WIDTH - 1.0;
	f_y = -(2 * y / HEIGHT - 1.0);
	screen_vec = vec3_add(\
	vec3_add(vec3_add(rt->camera->point, \
	vec3_mul(rt->camera->normalized, camera2screen)), \
	vec3_mul(screen_unit_vec.x_unit_vector, f_x)), \
	vec3_mul(screen_unit_vec.y_unit_vector, f_y));
	return (vec3_normalize(vec3_sub(screen_vec, rt->camera->point)));
}
