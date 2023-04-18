/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:07:40 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:09:09 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

double	vec3_mag(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	double	bunbo;
	t_vec3	ret;

	bunbo = vec3_mag(vec);
	ret.x = vec.x / bunbo;
	ret.y = vec.y / bunbo;
	ret.z = vec.z / bunbo;
	return (ret);
}
