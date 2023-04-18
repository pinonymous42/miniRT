/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:45:57 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:01:39 by tasano           ###   ########.fr       */
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
#include "draw.h"

void my_put_pixel(t_rt *rt, t_object *min_object, t_vec3 dir_vec, int x, int y)
{
	double	min;
	t_fcolor color;
	double shadow;

	min = min_object->t;
	shadow = check_shadow(rt, dir_vec, min);
	color = get_pixcel_color(min_object, min, rt, shadow, dir_vec);
	mlx_pixel_put(rt->game.mlx, rt->game.win, x, y, rgb_to_int(color));
}

int draw(t_rt *rt, double x, double y)
{
	t_vec3		dir_vec;
	t_object	*min_object;

	dir_vec = get_dir_vec(x, y, rt);
	get_t_val(rt->objects, rt->camera->point, dir_vec, 1);
	min_object = get_min_object(rt->objects);
	my_put_pixel(rt, min_object, dir_vec, x, y);
	return (0);
}

int draw_miniRT(t_rt *rt)
{
	double x;
	double y;

	y = -1;
	rt->camera->normalized = vec3_normalize(rt->camera->normalized); 
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			draw(rt, x, y);
	}
	return (0);
}