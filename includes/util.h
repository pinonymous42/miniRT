/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:12:31 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 20:02:31 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "vector.h"
# include "color.h"
# include "miniRT.h"

void		free_args(char **argv);

t_fcolor	rgb_init(int r, int g, int b);
int			rgb_to_int(t_fcolor color);
t_fcolor	add_color(t_fcolor c1, t_fcolor c2, double multi);

t_vec3		vec3_init(double x, double y, double z);
t_vec3		vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_sub(t_vec3 vec1, t_vec3 vec2);
double		vec3_mag(t_vec3 vec);
t_vec3		vec3_normalize(t_vec3 vec);
t_vec3		vec3_mul(t_vec3 vec, double scalar);
double		vec3_dot(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_cross(t_vec3 vec1, t_vec3 vec2);

void		delete_rt(t_rt *rt);

#endif