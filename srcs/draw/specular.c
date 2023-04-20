/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:01:12 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 19:37:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "vector.h"
#include "material.h"
#include <math.h>

static double	get_dot_2(t_vec3 reverse, t_vec3 reflection)
{
	double	dot_2;

	dot_2 = vec3_dot(reverse, reflection);
	if (dot_2 < 0)
		dot_2 = 0;
	return (dot_2);
}

double	specular(t_vec3 dir, t_vec3 reflect_normal, t_vec3 incident)
{
	t_vec3	reverse;
	t_vec3	reflection;
	t_vec3	tmp_mul;

	reverse = vec3_normalize(vec3_mul(dir, -1));
	tmp_mul = vec3_mul(vec3_mul(reflect_normal, \
				vec3_dot(incident, reflect_normal)), 2);
	reflection = vec3_normalize(vec3_sub(tmp_mul, incident));
	return (pow(get_dot_2(reverse, reflection), SHININESS) * KSPE);
}
