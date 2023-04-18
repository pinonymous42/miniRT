/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:38:37 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 16:28:46 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
#define DRAW_H

#include "vector.h"
#include "color.h"
#include "object.h"
#include "miniRT.h"
#include "libft.h"

#define EPSILON 1.0/512

t_fcolor	diffusion(t_vec3 incident_vec, t_vec3 reflect_normal_vec, t_object *object, t_fcolor new);
t_vec3		get_dir_vec(double x, double y, t_rt *rt);
t_object	*get_min_object(t_list *lst);
double		check_shadow(t_rt *rt, t_vec3 dir_vec, double min);
t_fcolor	get_pixcel_color(t_rt *rt, double shadow, t_vec3 dir_vec);
t_fcolor	specular(t_vec3 dir_vec, t_vec3 reflect_normal_vec, t_vec3 incident_vec, t_fcolor new, t_fcolor light_color, double light_power);
t_vec3		determin(t_rt *rt, t_vec3 crosspoint, t_vec3 dir, double min);
double		get_t_val(t_list *lst, t_vec3 start_vec, t_vec3 dir_vec, int shadow);
t_vec3		get_crosspoint_vec(t_vec3 camera_point, t_vec3 dir_vec, double min);
t_vec3		get_incident_vec(t_vec3 light_point, t_vec3 crosspoint_vec);
int			get_min(t_rt *rt);
#endif