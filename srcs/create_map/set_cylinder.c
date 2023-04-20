/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:43:02 by tasano            #+#    #+#             */
/*   Updated: 2023/04/20 14:59:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "create_map.h"

static int	check_cylinder(char **argv, t_cylinder *cylinder)
{
	t_vec3	tmp;

	tmp = cylinder->normalized;
	if (check_vec(argv[0]))
		return (CY_CENTER_ERR);
	if (check_vec(argv[1]))
		return (CY_NORMARIZE_ERR);
	if (check_vec_range(tmp, -1, 1))
		return (CY_NORMARIZE_RANGE_ERR);
	if (tmp.x == 0 && tmp.y == 0 && tmp.z == 0)
		return (CY_NORMARIZE_ERR);
	if (check_color(cylinder->color))
		return (CY_COLOR_ERR);
	if (cylinder->diameter <= 0)
		return (CY_DIAMETER_ERR);
	if (cylinder->height <= 0)
		return (CY_HEIGHT_ERR);
	return (0);
}

int	set_cylinder(t_rt *rt, char **argv)
{
	t_cylinder	*cylinder;
	int			status;

	if (!argv || !argv[0] || !argv[1] || !argv[2] || \
		!argv[3] || !argv[4] || argv[5])
		return (CY_DIF_ELEM_ERR);
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (MALLOC_ERR);
	cylinder->center = set_vec3(argv[0]);
	cylinder->normalized = set_vec3(argv[1]);
	cylinder->diameter = ft_atof(argv[2]);
	cylinder->height = ft_atof(argv[3]);
	cylinder->color = set_color(argv[4]);
	cylinder->front = NOTHING;
	status = check_cylinder(argv, cylinder);
	if (status)
		free (cylinder);
	else
		status = set_list(rt, (void *)cylinder, CYLINDER);
	return (status);
}
