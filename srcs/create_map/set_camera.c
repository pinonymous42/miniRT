/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:41:10 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 17:22:34 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"
#include "miniRT.h"
#include "create_map_errno.h"

int	check_camera(char **argv, t_camera *camera)
{
	if (check_vec(argv[0]))
		return (C_POINT_ERR);
	if (check_vec(argv[1]))
		return (C_NORMALIZE_ERR);
	if (check_vec_range(camera->normalized, -1, 1))
		return (C_NORMALIZE_RANGE_ERR);
	if (camera->fov < 0 || 180 < camera->fov)
		return (C_FOV_ERR);
	return (0);
}

int	set_camera(char **argv, t_rt *rt)
{
	if (rt->camera)
		return (C_DUP_ERR);
	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (C_FEW_ELEM_ERR);
	rt->camera = (t_camera *)malloc(sizeof(t_camera));
	if (!rt->camera)
		return (MALLOC_ERR);
	rt->camera->point = set_vec3(argv[0]);
	rt->camera->normalized = set_vec3(argv[1]);
	rt->camera->fov = ft_atoi(argv[2]);
	return (check_camera(argv, rt->camera));
}
