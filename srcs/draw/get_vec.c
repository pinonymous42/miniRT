/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:32:58 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 11:33:13 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3 get_crosspoint_vec(t_vec3 camera_point, t_vec3 dir_vec, double min)
{
	return (vec3_add(camera_point, vec3_mul(dir_vec, min)));
}

t_vec3 get_incident_vec(t_vec3 light_point, t_vec3 crosspoint_vec)
{
	return (vec3_normalize(vec3_sub(light_point, crosspoint_vec)));
}
