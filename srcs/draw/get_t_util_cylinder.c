/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_util_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:40:35 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 14:08:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_t_val.h"

t_compare get_compare(t_cylinder *cylinder, t_vec3 start_vec, t_vec3 dir_vec, t_tval t)
{
	t_compare compare;
	t_vec3 tmp_vec1;
	t_vec3 tmp_vec2;

	tmp_vec1 = vec3_sub(vec3_add(start_vec, vec3_mul(dir_vec, t.t1)), cylinder->center);
	tmp_vec2 = vec3_sub(vec3_add(start_vec, vec3_mul(dir_vec, t.t2)), cylinder->center);
	compare.compare1 = vec3_dot(tmp_vec1, cylinder->normalized);
	compare.compare2 = vec3_dot(tmp_vec2, cylinder->normalized);	

	return (compare);
}

int set_shadow(t_cylinder *cylinder, int shadow, int type)
{
	if (shadow)
		cylinder->front = type;
	return (0);
}

int check_val(double compare, double height, double t)
{
	return (0 <= compare && compare <= height && 0 < t);
}