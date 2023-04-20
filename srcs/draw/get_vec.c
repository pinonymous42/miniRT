/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:32:58 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:56:58 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	get_crosspoint_vec(t_vec3 camera, t_vec3 dir, double min)
{
	return (vec3_add(camera, vec3_mul(dir, min)));
}

t_vec3	get_incident_vec(t_vec3 light, t_vec3 crosspoint)
{
	return (vec3_normalize(vec3_sub(light, crosspoint)));
}
