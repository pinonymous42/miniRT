/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:45:04 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 14:59:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object.h"
#include "vector.h"
#include "draw.h"

double	check_shadow(t_rt *rt, t_vec3 dir_vec, double min)
{
	t_vec3	crosspoint_vec;
	t_vec3	incident_vec;

	crosspoint_vec = get_crosspoint_vec(rt->camera->point, dir_vec, min);
	incident_vec = get_incident_vec(rt->light->point, crosspoint_vec);
	get_t_val(rt->objects, vec3_add(crosspoint_vec, vec3_mul(incident_vec, EPSILON)), incident_vec, 0);
	return (get_min_object(rt->objects)->t);
}