/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:44 by tasano            #+#    #+#             */
/*   Updated: 2023/04/20 14:52:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"
#include "miniRT.h"
#include "create_map_errno.h"

static int	check_ambient(t_ambient *ambient)
{
	if (ambient->ratio < 0 || 1 < ambient->ratio)
		return (A_RATIO_ERR);
	if (check_color(ambient->color))
		return (A_COLOR_ERR);
	return (0);
}

int	set_ambient(char **argv, t_rt *rt)
{
	if (rt->ambient)
		return (A_DUP_ERR);
	if (!argv || !argv[0] || !argv[1] || argv[2])
		return (A_DIF_ELEM_ERR);
	rt->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!rt->ambient)
		return (MALLOC_ERR);
	rt->ambient->ratio = ft_atof(argv[0]);
	rt->ambient->color = set_color(argv[1]);
	return (check_ambient(rt->ambient));
}
