/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:27:27 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 14:55:17 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_t_val.h"
#include "libft.h"
#include <math.h>

double get_t_val_plane(t_plane *plane, t_vec3 start_vec, t_vec3 dir_vec)
{
	if (vec3_dot(dir_vec, plane->normalized) == 0)
		return (0);
	else if (vec3_dot(vec3_sub(plane->point, start_vec), plane->normalized) / vec3_dot(dir_vec, plane->normalized) < 0)
		return (0);
	else
		return (vec3_dot(vec3_sub(plane->point, start_vec), plane->normalized) / vec3_dot(dir_vec, plane->normalized));
}

double get_t_val_sphere(t_sphere *sphere, t_vec3 start_vec, t_vec3 dir_vec)
{
	t_condition con;
	
	con = get_condition_shpere(sphere, start_vec, dir_vec);
	if (con.a != 0 && con.d >= 0)
	{
		if (con.d == 0)
			return (-con.b / (2.0 * con.a));
		if (0 < con.t.t1 && 0 < con.t.t2)
			return (fmin(con.t.t1, con.t.t2));
		else if (con.t.t1 > 0 || con.t.t2 > 0)
			return (fmax(con.t.t1, con.t.t2));
	}
	return (0);
}

double get_t_val_cylinder(t_cylinder *cylinder, t_vec3 start_vec, t_vec3 dir_vec, int shadow)
{
	t_condition con;
	t_compare	compare;
	
	con = get_condition_cylinder(cylinder, start_vec, dir_vec);
	if (con.a != 0 && con.d >= 0)
	{
		if (con.d == 0)
			return (-con.b / (2 * con.a));
		compare = get_compare(cylinder, start_vec, dir_vec, con.t);
		if (check_val(compare.compare1, cylinder->height, con.t.t1))
		{
			set_shadow(cylinder, shadow, FRONT);
			return (con.t.t1);
		}
		else if (check_val(compare.compare2, cylinder->height, con.t.t2))
		{
			set_shadow(cylinder, shadow, BACK);
			return (con.t.t2);
		}
		else
			set_shadow(cylinder, shadow, NOTHING);
	}
	return (0);
}

double get_t_val(t_list *lst, t_vec3 start_vec, t_vec3 dir_vec, int shadow)
{
	t_object *tmp;
	t_list *tmp_lst;

	tmp_lst = lst;
	while (tmp_lst)
	{
		tmp = (t_object *)tmp_lst->content;
		if (tmp->type == SPHERE)
			tmp->t = get_t_val_sphere((t_sphere *)tmp->object, start_vec, dir_vec);
		else if (tmp->type == PLANE)
			tmp->t = get_t_val_plane((t_plane *)tmp->object, start_vec, dir_vec);
		else if (tmp->type == CYLINDER)
			tmp->t = get_t_val_cylinder((t_cylinder *)tmp->object, start_vec, dir_vec, shadow);
		tmp_lst = tmp_lst->next;
	}
	return (0);
}
