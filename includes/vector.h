/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:06:04 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 20:06:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3			vec3_init(double x, double y, double z);
t_vec3			vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec3_sub(t_vec3 vec1, t_vec3 vec2);
double			vec3_mag(t_vec3 vec);
t_vec3			vec3_normalize(t_vec3 vec);
t_vec3			vec3_mul(t_vec3 vec, double scalar);
double			vec3_dot(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec3_cross(t_vec3 vec1, t_vec3 vec2);

#endif