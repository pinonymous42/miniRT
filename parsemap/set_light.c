/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:39:06 by tasano            #+#    #+#             */
/*   Updated: 2023/03/31 20:39:13 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int set_light(char **argv, t_rt *rt)
{
	t_light *light;

	if (!argv || !argv[0] || !argv[1] || !argv[2])
		return (1);
	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (1);
	light->point = set_vec3(argv[0]);
	light->ratio = ft_atoi(argv[1]);
	light->color = set_color(argv[2]);
	ft_lstadd_back(&rt->lights, ft_lstnew((void *)light));
	return (0);
}