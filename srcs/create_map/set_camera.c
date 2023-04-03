/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:41:10 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 15:06:24 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"
#include "miniRT.h"

int check_camera(char **argv, t_camera *camera)
{
	if (check_vec(argv[0]))
		return (1);
	if (check_vec(argv[1]))
		return (1);
	if (check_vec_range(camera->normalized, -1, 1))
		return (1);
	if (camera->fov < 0 || 180 < camera->fov)
		return (1);
	return (0);
}

int set_camera(char **argv, t_rt *rt)
{
	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (1);
	rt->camera = (t_camera *)malloc(sizeof(t_camera));
	if (!rt->camera)
		return (1);
	rt->camera->point = set_vec3(argv[0]);
	rt->camera->normalized = set_vec3(argv[1]);
	rt->camera->fov = ft_atoi(argv[2]);
	if (check_camera(argv, rt->camera))
		return (1);
	return (0);
}
