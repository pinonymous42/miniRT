/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:27:57 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:06:41 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec3_init(double x, double y , double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	ret;
	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	ret;
	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	ret.z = vec1.z - vec2.z;
	return (ret);
}

double	vec3_mag(t_vec3 vec)//ベクトルの大きさ
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec3_normalize(t_vec3 vec)//ベクトルを正規化
{
	double bunbo;
	t_vec3 ret;

	bunbo = vec3_mag(vec);
	ret.x = vec.x / bunbo;
	ret.y = vec.y / bunbo;
	ret.z = vec.z / bunbo;
	return (ret);
}

t_vec3	vec3_mul(t_vec3 vec, double scalar)
{
	t_vec3 ret;

	ret.x = scalar * vec.x;
	ret.y = scalar * vec.y;
	ret.z = scalar * vec.z;
	return (ret);
}

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)//内積
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)//外積
{
	t_vec3	ret;

	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return (ret);
}