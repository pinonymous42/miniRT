#include "libft.h"
#include "mlx.h"
#include "combination.h"
#include "create_map.h"
#include "key_code.h"
#include "miniRT.h"
#include "mlx_info.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

#define NUMBER 2

double get_t_plane(t_vec3 dir_vec, t_vec3 start_vec, t_plane *plane)
{
	if (vec3_dot(dir_vec, plane->point) == 0)
		return (0);
	else if (vec3_dot(vec3_sub(plane->normalized, start_vec), plane->normalized) / vec3_dot(dir_vec, plane->normalized) < 0)
		return (0);
	else
		return ((vec3_dot(vec3_sub(plane->point, start_vec), plane->normalized) / vec3_dot(dir_vec, plane->normalized)));
}

double get_t_sphere(t_vec3 dir_vec, t_vec3 start_vec, t_sphere *sphere)
{
	double a = 0;
	double b = 0;
	double c = 0;
	double t;
	double t1 = 0, t2 = 0;

	t_vec3 camera2sphere_vec = vec3_sub(start_vec, sphere->center); // カメラから球へのベクトル
	a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
	b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
	c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - sphere->diameter * sphere->diameter;
	double D = b * b - 4 * a * c;
	if (a != 0 && D >= 0)
	{
		// 交差判定
		if (D == 0)				// 接する時
			t = -b / (2.0 * a); // 媒介変数tの長さ
		else if (D > 0)			// 交わる時
		{
			t1 = (-b - sqrt(D)) / (2.0 * a);
			t2 = (-b + sqrt(D)) / (2.0 * a);

			if (t1 > 0 && t2 > 0) // 両方正なら小さい方をtとする。
			{
				if (t1 > t2)
					t = t2;
				else
					t = t1;
			}
			else // 片方正なら、それをtとする。
			{
				if (t1 > 0)
					t = t1;
				else if (t2 > 0)
					t = t2;
				else
					t = 0;
			}
		}
		else
			t = 0;
	}
	return (t);
}

double get_t_cylinder(t_vec3 dir_vec, t_vec3 start_vec, t_cylinder *cylinder, int shadow)
{
	double a;
	double b;
	double c;
	double t;
	double t1 = 0, t2 = 0;

	t_vec3 tmp_vec = vec3_sub(start_vec, cylinder->center);
	t_vec3 tmp_cross = vec3_cross(dir_vec, cylinder->normalized);
	t_vec3 tmp_vec_and_cross = vec3_cross(tmp_vec, cylinder->normalized);
	a = vec3_mag(tmp_cross) * vec3_mag(tmp_cross);
	b = 2 * vec3_dot(tmp_cross, tmp_vec_and_cross);
	c = vec3_mag(tmp_vec_and_cross) * vec3_mag(tmp_vec_and_cross) - cylinder->diameter * cylinder->diameter;
	// 判別式
	double D = b * b - 4 * a * c;
	if (a != 0 && D >= 0)
	{
		// 交差判定
		if (D == 0)				// 接する時
			t = -b / (2.0 * a); // 媒介変数tの長さ
		else if (D > 0)			// 交わる時
		{
			t1 = (-b - sqrt(D)) / (2.0 * a);
			t2 = (-b + sqrt(D)) / (2.0 * a);

			double compare1 = vec3_dot(vec3_sub(vec3_add(start_vec, vec3_mul(dir_vec, t1)), object_list[i].vec), object_list[i].normal_vec);
			double compare2 = vec3_dot(vec3_sub(vec3_add(start_vec, vec3_mul(dir_vec, t2)), object_list[i].vec), object_list[i].normal_vec);
			if (0 <= compare1 && compare1 <= object_list[i].height && t1 > 0)
			{
				t = t1;
				if (shadow)
					object_list[i].cylinder_front_or_back = FRONT;
			}
			else if (0 <= compare2 && compare2 <= object_list[i].height && t2 > 0)
			{
				t = t2;
				if (shadow)
					object_list[i].cylinder_front_or_back = BACK;
			}
			else
			{
				t = 0;
				if (shadow)
					object_list[i].cylinder_front_or_back = NOTHING;
			}
		}
	}
	else
		t = 0;
	return (t);
}

double get_t_value(t_vec3 start_vec, t_vec3 dir_vec, t_object *object, int shadow) // 交差判定
{
	double t;

	if (object->type == SPHERE)
		t = get_t_sphere(dir_vec, start_vec, (t_sphere *)object->object);
	else if (object->type == CYLINDER)
		t = get_t_cylinder(dir_vec, start_vec, (t_cylinder *)object->object, shadow);
	else if (object->type == PLANE)
		t = get_t_plane(dir_vec, start_vec, (t_plane *)object->object);
	return (t);
}

int get_min_index(double *t, int number)
{
	int i;
	double min;
	int min_index;

	for (i = 0; i < number; i++)
	{
		if (t[i] != 0)
		{
			min = t[i];
			min_index = i;
			break;
		}
		min = 0;
		min_index = 0;
	}
	if (min != 0)
	{
		for (i = 0; i < number; i++)
		{
			if (t[i] < min && t[i] != 0)
			{
				min = t[i];
				min_index = i;
			}
		}
	}
	return (min_index);
}

double check_shadow(t_vec3 crosspoint_vec, t_vec3 incident_vec, double epsilon, t_object *object)
{
	double *check_shadow = (double *)malloc(sizeof(double) * NUMBER);
	int tmp_min_index;
	int index;
	double shadow_min;
	index = 0;
	while (index < NUMBER)
	{
		check_shadow[index] = get_t_value(vec3_add(crosspoint_vec, vec3_mul(incident_vec, epsilon)), incident_vec, object, 0);
		index++;
	} 
	tmp_min_index = get_min_index(check_shadow, NUMBER);
	shadow_min = check_shadow[tmp_min_index];
	free(check_shadow);
	return (shadow_min);
}

t_vec3 determin_normal_vec(t_objects *object_list, t_vec3 crosspoint_vec, int i, t_vec3 camera_vec, double *t, t_vec3 dir_vec)
{
	t_vec3 normal_vec = vec3_init(1, 1, 1);

	if (object_list[i].kind == SPHERE)
		normal_vec = vec3_normalize(vec3_sub(crosspoint_vec, object_list[i].vec)); // 法線ベクトル
	else if (object_list[i].kind == PLANE)
		normal_vec = object_list[i].normal_vec;
	else if (object_list[i].kind == CYLINDER)
	{
		t_vec3 tmp_vec = vec3_sub(vec3_add(camera_vec, vec3_mul(dir_vec, t[i])), object_list[i].vec);
		if (object_list[i].cylinder_front_or_back == FRONT)
		{
			normal_vec = vec3_normalize(vec3_sub(tmp_vec, vec3_mul(object_list[i].normal_vec, vec3_dot(tmp_vec, object_list[i].normal_vec))));
		}
		else if (object_list[i].cylinder_front_or_back == BACK)
		{
			normal_vec = vec3_mul(vec3_normalize(vec3_sub(tmp_vec, vec3_mul(object_list[i].normal_vec, vec3_dot(tmp_vec, object_list[i].normal_vec)))), -1);
		}
	}
	return (normal_vec);
}

t_fcolor diffusion(t_vec3 incident_vec, t_vec3 reflect_normal_vec, t_object *object, int i, t_fcolor new)
{
	double diffusion = 0;
	double dot_1;
	if (vec3_dot(incident_vec, reflect_normal_vec) <= 0)
		dot_1 = 0;
	else
		dot_1 = vec3_dot(incident_vec, reflect_normal_vec);
	//diffusion = dot_1 * object.material.kDif;
	diffusion = dot_1 * 0.6;
	return (add_color(new, object->color, diffusion));
}

t_fcolor specular(t_vec3 dir_vec, t_vec3 reflect_normal_vec,
				  t_vec3 incident_vec, t_objects *object_list, t_fcolor new,
				  t_fcolor light_color, double light_power, int i)
{
	double specular = 0;
	t_vec3 reverse_dir_vec = vec3_normalize(vec3_mul(dir_vec, -1)); // 視線ベクトルの逆向き
	t_vec3 regular_reflection_vec = vec3_normalize(vec3_sub(vec3_mul(vec3_mul(reflect_normal_vec, vec3_dot(incident_vec, reflect_normal_vec)), 2), incident_vec));
	double dot_2;
	if (vec3_dot(reverse_dir_vec, regular_reflection_vec) < 0)
		dot_2 = 0;
	else
		dot_2 = vec3_dot(reverse_dir_vec, regular_reflection_vec);
	specular = pow(dot_2, object_list[i].material.shininess) * object_list[i].material.kSpe;
	return (add_color(new, light_color, light_power * specular));
}

void my_put_pixel(t_vec3 camera_vec, t_vec3 dir_vec, t_vec3 light_vec, t_object *object, double *t,
				  int i, double light_power, double ambient_power, t_game *game, double x, double y, double epsilon,
				  t_fcolor light_color, t_fcolor ambient_color)
{
	t_fcolor new = rgb_init(0, 0, 0);
	t_vec3 crosspoint_vec = vec3_add(camera_vec, vec3_mul(dir_vec, t[i]));	   // 視線と物体の交点の位置ベクトル
	t_vec3 incident_vec = vec3_normalize(vec3_sub(light_vec, crosspoint_vec)); // 入射ベクトル(入射って言ってるけど、向きに注意)

	new = add_color(new, ambient_color, ambient_power);

	// 影かどうか
	double distance = vec3_mag(vec3_sub(light_vec, crosspoint_vec)) - epsilon;
	double shadow;
	shadow = check_shadow(crosspoint_vec, incident_vec, epsilon, object);
	t_vec3 reflect_normal_vec;
	if (shadow == 0 || distance < vec3_mag(vec3_add(crosspoint_vec, vec3_mul(incident_vec, epsilon + shadow))))
	{
		reflect_normal_vec = determin_normal_vec(object, crosspoint_vec, i, camera_vec, t, dir_vec);
		new = diffusion(incident_vec, reflect_normal_vec, object, i, new);
		new = specular(dir_vec, reflect_normal_vec, incident_vec, object, new, light_color, light_power, i);
	}
	if (t[i] > 0)
		mlx_pixel_put(game->mlx, game->win, x, y, rgb_to_int((int)new.red, (int)new.green, (int)new.blue));
	else
		mlx_pixel_put(game->mlx, game->win, x, y, rgb_to_int(255, 255, 255));
}

t_orthonormal init_unit(t_vec3 camera_vec, t_vec3 camera_normal_vec)
{
	t_orthonormal ret;

	vec3_add(camera_vec, camera_normal_vec);   // おそらく不要
	t_vec3 y_unit_vector = vec3_init(0, 1, 0); //(0, 1, 0)の単位ベクトル。これを定義しないと自由に回転できちゃう。
	ret.x_unit_vector = vec3_cross(y_unit_vector, camera_normal_vec);
	ret.y_unit_vector = vec3_cross(camera_normal_vec, ret.x_unit_vector);
	return (ret);
}

int main_loop(t_rt *rt)
{
	double theta = rt->camera->fov;									  // FOV
	double camera2screen = 2 / (2 * tan(((theta / 180 * M_PI) / 2))); // カメラからスクリーンまでの距離
	double epsilon = 1.0 / 512;										  // 微小距離
	t_vec3 camera_vec = rt->camera->point;							  // 視点位置のベクトル
	t_vec3 camera_normal_vec = rt->camera->normalized;				  // 視点位置の法線ベクトル
	t_orthonormal screen_unit_vec = init_unit(camera_vec, camera_normal_vec);
	double light_power = rt->light->ratio;
	t_fcolor light_color = rt->light->color;
	t_vec3 light_vec = rt->light->point; // 光源の位置ベクトル
	double ambient_power = rt->ambient.ratio;
	t_fcolor ambient_color = rt->ambient.color;
	size_t size = ft_lstsize(rt->objects);

	int i;
	int min_index;
	t_list *head;
	head = rt->objects;
	for (double y = 0; y < HEIGHT; y++)
	{
		rt->objects = head;
		for (double x = 0; x < WIDTH; x++)
		{
			double f_x = 2 * x / WIDTH - 1.0;
			double f_y = -(2 * y / HEIGHT - 1.0);
			double *t = (double *)malloc(sizeof(double) * size);
			t_vec3 screen_vec = vec3_add(vec3_add(vec3_add(camera_vec, vec3_mul(camera_normal_vec, camera2screen)), vec3_mul(screen_unit_vec.x_unit_vector, f_x)), vec3_mul(screen_unit_vec.y_unit_vector, f_y)); // スクリーン上の点の三次元空間におけるベクトル
			t_vec3 dir_vec = vec3_normalize(vec3_sub(screen_vec, camera_vec));																																	  // 方向ベクトル(視線ベクトル)

			while (rt->objects)
			{
				t[i] = get_t_value(camera_vec, dir_vec, (t_object *)rt->objects->content, 1);
				rt->objects =rt->objects->next;
			}
			rt->objects = head;
			min_index = get_min_index(t, size);
			my_put_pixel(camera_vec, dir_vec, light_vec, rt->objects, t, min_index, light_power,
						 ambient_power, &rt->game, x, y, epsilon, light_color, ambient_color);
			free(t);
		}
	}
	return (0);
}