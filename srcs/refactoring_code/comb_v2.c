/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comb_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:45:57 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 14:27:37 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "miniRT.h"
#include "mlx.h"
#include "mlx_info.h"
#include "vector.h"
#include "color.h"
#include "object.h"
#include <math.h>

typedef struct s_orthonormal
{
	t_vec3 x_unit_vector;
	t_vec3 y_unit_vector;
} t_orthonormal;

t_orthonormal init_unit(t_vec3 camera_normal_vec)
{
	t_orthonormal ret;

	t_vec3 y_unit_vector = vec3_init(0, 1, 0); //(0, 1, 0)の単位ベクトル。これを定義しないと自由に回転できちゃう。
	ret.x_unit_vector = vec3_cross(y_unit_vector, camera_normal_vec);
	ret.y_unit_vector = vec3_cross(camera_normal_vec, ret.x_unit_vector);
	return (ret);
}

t_vec3 get_dir_vec(double x, double y, t_rt *rt)
{
	t_vec3 screen_vec;
	t_orthonormal screen_unit_vec = init_unit( rt->camera->normalized);
	double f_x;
	double f_y;
	double camera2screen;

	camera2screen = 2 / (2 * tan((((double)rt->camera->fov / 180 * M_PI) / 2))); // カメラからスクリーンまでの距離
	f_x = 2 * x / WIDTH - 1.0;
	f_y = -(2 * y / HEIGHT - 1.0);

	screen_vec = vec3_add(\
	vec3_add(vec3_add(rt->camera->point,\
	vec3_mul(rt->camera->normalized, camera2screen)), \
	vec3_mul(screen_unit_vec.x_unit_vector, f_x)), \
	vec3_mul(screen_unit_vec.y_unit_vector, f_y)); // スクリーン上の点の三次元空間におけるベクトル
	return (vec3_normalize(vec3_sub(screen_vec, rt->camera->point)));
}

t_object *get_min_object(t_list *lst)
{
	t_object *object;
	t_object *min_object;
	t_list *head;

	head = lst;
	while (lst)
	{
		object = (t_object *)lst->content;
		if (object->t != 0)
		{
			min_object = object;
			break;
		}
		min_object = (t_object *)head->content;
		min_object->t = 0;
		lst = lst->next;
	}
	lst = head;
	if (min_object->t != 0)
	{
		while (lst)
		{
			object = (t_object *)lst->content;
			if (object->t != 0 && object->t < min_object->t)
				min_object = object;
			lst = lst->next;
		}
	}
	return (min_object);
}

t_fcolor diffusion(t_vec3 incident_vec, t_vec3 reflect_normal_vec, t_object *object, t_fcolor new)
{
	double diffusion;
	double dot_1;

	dot_1 = vec3_dot(incident_vec, reflect_normal_vec);
	if (dot_1 <= 0)
		dot_1 = 0;
	diffusion = dot_1 * 0.69;
	if (object->type == SPHERE)
	{
		t_sphere *content = object->object;
		return (add_color(new, content->color, diffusion));
	}
	else if (object->type == PLANE)
	{
		t_plane *content = object->object;
		return (add_color(new, content->color, diffusion));
	}
	else
	{
		t_cylinder *content = object->object;
		return (add_color(new, content->color, diffusion));
	}
}

t_fcolor specular(t_vec3 dir_vec, t_vec3 reflect_normal_vec,
				  t_vec3 incident_vec, t_fcolor new,
				  t_fcolor light_color, double light_power)
{
	double specular = 0;
	t_vec3 reverse_dir_vec = vec3_normalize(vec3_mul(dir_vec, -1)); // 視線ベクトルの逆向き
	t_vec3 regular_reflection_vec = vec3_normalize(vec3_sub(vec3_mul(vec3_mul(reflect_normal_vec, vec3_dot(incident_vec, reflect_normal_vec)), 2), incident_vec));
	double dot_2;
	double shining = 8;
	double Kspe = 0.3;

	if (vec3_dot(reverse_dir_vec, regular_reflection_vec) < 0)
		dot_2 = 0;
	else
		dot_2 = vec3_dot(reverse_dir_vec, regular_reflection_vec);
	specular = pow(dot_2, shining) * Kspe;
	return (add_color(new, light_color, light_power * specular));
}

double	check_shadow(t_vec3 crosspoint_vec, t_vec3 incident_vec, double epsilon, t_list *object_lst)
{
	t_object *tmp;
	t_list *tmp_lst;

	tmp_lst = object_lst;
	while (tmp_lst)
	{
		tmp = (t_object *)tmp_lst->content;
		tmp->t = get_t_val(tmp, vec3_add(crosspoint_vec, vec3_mul(incident_vec, epsilon)), incident_vec, 0);
		tmp_lst = tmp_lst->next;
	}
	return (get_min_object(object_lst)->t);
}

void my_put_pixel(t_rt *rt, t_object *min_object, t_vec3 dir_vec, int x, int y)
{
	double epsilon = 1.0 / 512;
	double	min = min_object->t;
	t_fcolor new = rgb_init(0, 0, 0);
	t_vec3 crosspoint_vec = vec3_add(rt->camera->point, vec3_mul(dir_vec, min)); // 視線と物体の交点の位置ベクトル
	t_vec3 incident_vec = vec3_normalize(vec3_sub(rt->light->point, crosspoint_vec));	   // 入射ベクトル(入射って言ってるけど、向きに注意)
	new = add_color(new, rt->ambient->color, rt->ambient->ratio);

	// 影かどうか
	double distance = vec3_mag(vec3_sub(rt->light->point, crosspoint_vec)) - epsilon;
	double shadow = 0;
	shadow = check_shadow(crosspoint_vec, incident_vec, epsilon, rt->objects);
	t_vec3 reflect_normal_vec;
	if (shadow == 0 || distance < vec3_mag(vec3_add(crosspoint_vec, vec3_mul(incident_vec, epsilon + shadow))))
	{
		reflect_normal_vec = determin_normal_vec(rt, min_object, crosspoint_vec, dir_vec, min);
		new = diffusion(incident_vec, reflect_normal_vec, min_object, new);
		new = specular(dir_vec, reflect_normal_vec, incident_vec, new, rt->light->color, rt->light->ratio);
	}
	if (min > 0)
		mlx_pixel_put(rt->game.mlx, rt->game.win, x, y, rgb_to_int(new.red, new.green, new.blue));
	else
		mlx_pixel_put(rt->game.mlx, rt->game.win, x, y, rgb_to_int(255, 255, 255));
}

int draw(t_rt *rt, double x, double y)
{
	t_vec3 dir_vec;
	t_list *tmp_lst;
	t_object *tmp;


	dir_vec = get_dir_vec(x, y, rt);
	tmp_lst = rt->objects;
	while (tmp_lst)
	{
		tmp = (t_object *)tmp_lst->content;
		tmp->t = get_t_val(tmp, rt->camera->point, dir_vec, 1);
		tmp_lst = tmp_lst->next;
	}
	t_object *min_object = get_min_object(rt->objects);
	my_put_pixel(rt, min_object, dir_vec, x, y);
	return (0);
}

int draw_miniRT(t_rt *rt)
{
	double x;
	double y;

	y = -1;
	rt->camera->normalized = vec3_normalize(rt->camera->normalized); //視点位置の法線ベクトル
	
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			draw(rt, x, y);
	}
	return (0);
}