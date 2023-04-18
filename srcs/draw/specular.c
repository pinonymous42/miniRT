/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:01:12 by tasano            #+#    #+#             */
/*   Updated: 2023/04/16 19:47:40 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "vector.h"
#include "material.h"
#include <math.h>

static double	get_dot_2(t_vec3 reverse_dir_vec, t_vec3 regular_reflection_vec)
{
	double	dot_2;

	dot_2 = vec3_dot(reverse_dir_vec, regular_reflection_vec);
	if (dot_2 < 0)
		dot_2 = 0;
	return (dot_2);
}

t_fcolor specular(t_vec3 dir_vec, t_vec3 reflect_normal_vec, t_vec3 incident_vec, t_fcolor new, t_fcolor light_color, double light_power)
{
	double	specular;
	t_vec3	reverse_dir_vec = vec3_normalize(vec3_mul(dir_vec, -1)); // 視線ベクトルの逆向き
	t_vec3	regular_reflection_vec = vec3_normalize(vec3_sub(vec3_mul(vec3_mul(reflect_normal_vec, vec3_dot(incident_vec, reflect_normal_vec)), 2), incident_vec));
	double	dot_2;

	dot_2 = get_dot_2(reverse_dir_vec, regular_reflection_vec);
	specular = pow(dot_2, SHININESS) * KSPE;
	return (add_color(new, light_color, light_power * specular));
}