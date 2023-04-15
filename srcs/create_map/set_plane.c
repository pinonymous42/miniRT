/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:52:49 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 01:08:15 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "create_map.h"

static int check_plane(char **argv, t_plane *plane)
{
	if (check_vec(argv[0]))
		return (PL_POINT_ERR);
	if (check_vec(argv[1]))
		return (PL_NORMARIZE_ERR);
	if (check_vec_range(plane->normalized, -1, 1))
		return (PL_NORMARIZE_ERR);
	if (check_color(plane->color))
		return (PL_COLOR_ERR);
	return (0);
}

int set_plane(t_rt *rt, char **argv)
{
	t_plane *plane;
	int		status;
	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (MALLOC_ERR);
	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (MALLOC_ERR);
	plane->point = set_vec3(argv[0]);
	plane->normalized = set_vec3(argv[1]);
	plane->color = set_color(argv[2]);
	status = check_plane(argv, plane);
	if (status)
		free(plane);
	else
		status = set_list(rt, (void *)plane, pl);
	return (status);
}
