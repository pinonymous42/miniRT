/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:41:10 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 17:18:36 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_camera *camera;

	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (1);
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		return (1);
	camera->point = set_vec3(argv[0]);
	camera->normalized = set_vec3(argv[1]);
	camera->fov = ft_atoi(argv[2]);
	if (check_camera(argv, camera))
	{
		free(camera);
		return (1);
	}
	ft_lstadd_back(&rt->cameras, ft_lstnew((void *)camera));
	return (0);
}
