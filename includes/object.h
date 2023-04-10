/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:08:11 by tasano            #+#    #+#             */
/*   Updated: 2023/04/09 13:45:07 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "color.h"

#define sp 0
#define pl 1
#define cy 2

// sp Sphere
typedef struct s_sphere
{
	t_vec3 center;
	double diameter;
	t_fcolor color;
} t_sphere;

// pl Plane
typedef struct s_plane
{
	t_vec3 point;
	t_vec3 normalized;
	t_fcolor color;
} t_plane;

// cy Cylinder
typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 normalized;
	double diameter;
	double height;
	t_fcolor color;
	int		front;
} t_cylinder;

typedef struct s_object
{
	void *object;
	int type;
	double t;
} t_object;

#endif