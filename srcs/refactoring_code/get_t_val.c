/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:27:27 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 20:43:49 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "object.h"
#include <math.h>
#include <stdio.h>
double get_t_val_plane(t_plane *plane, t_vec3 start_vec, t_vec3 dir_vec)
{
	if (vec3_dot(dir_vec, plane->normalized) == 0)
		return (0);
	else if (vec3_dot(vec3_sub(plane->point, start_vec), plane->normalized) / vec3_dot(dir_vec, plane->normalized) < 0)
		return (0);
	else
		return (vec3_dot(vec3_sub(plane->point, start_vec), plane->normalized) / vec3_dot(dir_vec, plane->normalized));
}

double get_t_val_sphere(t_sphere *sphere, t_vec3 start_vec, t_vec3 dir_vec)
{
	double a;
	double b;
	double c;
	double d;
	double t1;
	double t2;

	t_vec3 camera2sphere_vec = vec3_sub(start_vec, sphere->center); // カメラから球へのベクトル
	// printf("x: %f, y: %f, z: %f\n", camera2sphere_vec.x, camera2sphere_vec.y, camera2sphere_vec.z);
	a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
	b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
	c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - sphere->diameter * sphere->diameter;
	d = b * b - 4 * a * c;
	if (a != 0 && d >= 0)
	{
		if (d == 0)
			return (-b / (2.0 * a));
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);
		if (0 < t1 && 0 < t2)
		{
			if (t1 < t2)
				return (t1);
			else
				return (t2);
		}
		else if (t1 > 0 || t2 > 0)
		{
			if (t1 > t2)
				return (t1);
			else
				return (t2);
		}
	}
	return (0);
}

double get_t_val_cylinder(t_cylinder *cylinder, t_vec3 start_vec, t_vec3 dir_vec, int shadow)
{
	double a;
	double b;
	double c;
	double d;
	double t1;
	double t2;

	t_vec3 tmp_vec = vec3_sub(start_vec, cylinder->center);
	t_vec3 tmp_cross = vec3_cross(dir_vec, cylinder->normalized);
	t_vec3 tmp_vec_and_cross = vec3_cross(tmp_vec, cylinder->normalized);
	a = vec3_mag(tmp_cross) * vec3_mag(tmp_cross);
	b = 2 * vec3_dot(tmp_cross, tmp_vec_and_cross);
	c = vec3_mag(tmp_vec_and_cross) * vec3_mag(tmp_vec_and_cross) - pow(cylinder->diameter, 2);
	d = b * b - 4 * a * c;
	if (a != 0 && d >= 0)
	{
		if (d == 0)
			return (-b / (2 * a));
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);
		double compare1 = vec3_dot(vec3_sub(vec3_add(start_vec, vec3_mul(dir_vec, t1)), cylinder->center), cylinder->normalized);
		double compare2 = vec3_dot(vec3_sub(vec3_add(start_vec, vec3_mul(dir_vec, t2)), cylinder->center), cylinder->normalized);
		if (0 <= compare1 && compare1 <= cylinder->height && t1 > 0)
		{
			if (shadow)
				cylinder->front = FRONT;
			return (t1);
		}
		else if (0 <= compare2 && compare2 <= cylinder->height && t2 > 0)
		{
			if (shadow)
				cylinder->front = BACK;
			return (t2);
		}
		else if (shadow)
			cylinder->front = NOTHING;
	}
	return (0);
}

double get_t_val(t_object *object, t_vec3 start_vec, t_vec3 dir_vec, int shadow)
{
	if (object->type == SPHERE)
		return (get_t_val_sphere((t_sphere *)object->object, start_vec, dir_vec));
	else if (object->type == PLANE)
		return (get_t_val_plane((t_plane *)object->object, start_vec, dir_vec));
	else if (object->type == CYLINDER)
		return (get_t_val_cylinder((t_cylinder *)object->object, start_vec, dir_vec, shadow));
	return (0);
}
