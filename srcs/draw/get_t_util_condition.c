/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_util_condition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:33:11 by tasano            #+#    #+#             */
/*   Updated: 2023/04/19 00:15:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_t_val.h"
#include <math.h>

static t_tval	get_tval(t_condition con)
{
	t_tval	t;

	t.t1 = (-con.b - sqrt(con.d)) / (2 * con.a);
	t.t2 = (-con.b + sqrt(con.d)) / (2 * con.a);
	return (t);
}

t_condition	get_condition_cylinder(t_cylinder *cylinder, \
					t_vec3 start_vec, t_vec3 dir_vec)
{
	t_condition	con;
	t_vec3		tmp_vec;
	t_vec3		tmp_cross;
	t_vec3		tmp_vec_and_cross;

	tmp_vec = vec3_sub(start_vec, cylinder->center);
	tmp_cross = vec3_cross(dir_vec, cylinder->normalized);
	tmp_vec_and_cross = vec3_cross(tmp_vec, cylinder->normalized);
	con.a = vec3_mag(tmp_cross) * vec3_mag(tmp_cross);
	con.b = 2 * vec3_dot(tmp_cross, tmp_vec_and_cross);
	con.c = pow(vec3_mag(tmp_vec_and_cross), 2) - pow(cylinder->diameter / 2, 2);
	con.d = con.b * con.b - 4 * con.a * con.c;
	if (con.a == 0 || con.d == 0 || con.d < 0)
		return (con);
	con.t = get_tval(con);
	return (con);
}

t_condition	get_condition_shpere(t_sphere *sphere, \
							t_vec3 start_vec, t_vec3 dir_vec)
{
	t_condition	con;
	t_vec3		camera2sphere_vec;

	camera2sphere_vec = vec3_sub(start_vec, sphere->center);
	con.a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
	con.b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
	con.c = vec3_dot(camera2sphere_vec, camera2sphere_vec) \
			- pow(sphere->diameter / 2, 2);
	con.d = con.b * con.b - 4 * con.a * con.c;
	if (con.a == 0 || con.d == 0 || con.d < 0)
		return (con);
	con.t = get_tval(con);
	return (con);
}
