/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_val.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:03:41 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 14:54:47 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_T_VAL_H
#define GET_T_VAL_H

#include "object.h"

typedef struct s_tval
{
	double t1;
	double t2;
} t_tval;

typedef struct s_compare
{
	double	compare1;
	double	compare2;
} t_compare;

typedef struct  s_condition
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_tval	t;
} t_condition;

int			check_val(double compare, double height, double t);
int			set_shadow(t_cylinder *cylinder, int shadow, int type);
t_compare	get_compare(t_cylinder *cylinder, t_vec3 start_vec, t_vec3 dir_vec, t_tval t);
t_condition	get_condition_shpere(t_sphere *sphere, t_vec3 start_vec, t_vec3 dir_vec);
t_condition	get_condition_cylinder(t_cylinder *cylinder, t_vec3 start_vec, t_vec3 dir_vec);


#endif