/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:38:07 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 13:56:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_cylinder *set_cylinder(char **argv)
{
	t_cylinder *cylinder;

	if (!argv || !argv[0] || !argv[1] || !argv[2] || !argv[3] || !argv[4])
		return (NULL);
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = set_vec3(argv[0]);
	cylinder->normalized = set_vec3(argv[1]);
	cylinder->diameter = atof(argv[2]);
	cylinder->height = atof(argv[3]);
	cylinder->color = set_color(argv[4]);
	return (cylinder);
}

static t_plane *set_plane(char **argv)
{
	t_plane *plane;

	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (NULL);
	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = set_vec3(argv[0]);
	plane->normalized = set_vec3(argv[1]);
	plane->color = set_color(argv[2]);
	return (plane);
}

static t_sphere *set_sphere(char **argv)
{
	t_sphere *sphere;

	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (NULL);
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = set_vec3(argv[0]);
	sphere->diameter = atof(argv[1]);
	sphere->color = set_color(argv[2]);
	return (sphere);
}

int set_object(char **elements, t_rt *rt)
{
	t_object *object;

	object = (t_object *)malloc(sizeof(t_object));
	if (!object)
		return (1);
	if (ft_strncmp("sp", elements[0], 2) == 0)
	{
		object->object = (t_object *)set_sphere(++elements);
		object->type = sp;
	}
	if (ft_strncmp("pl", elements[0], 2) == 0)
	{
		object->object = (t_object *)set_plane(++elements);
		object->type = pl;
	}
	if (ft_strncmp("cy", elements[0], 2) == 0)
	{
		object->object = (t_object *)set_cylinder(++elements);
		object->type = cy;
	}
	if (!object->object)
		return (1);
	ft_lstadd_back(&rt->objects, ft_lstnew((void *)object));
	return (0);
}