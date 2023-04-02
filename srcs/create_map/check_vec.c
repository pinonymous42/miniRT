/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:05:52 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 09:16:23 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"

int check_vec_range(t_vec3 vec, double min, double max)
{
	if (vec.x < min || max < vec.x)
		return (1);
	if (vec.y < min || max < vec.y)
		return (1);
	if (vec.z < min || max < vec.z)
		return (1);
	return (0);
}

int check_vec(char *vec_str)
{
	char **tmp;

	tmp = ft_split(vec_str, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		return (1);
	}
	if (check_double(tmp[0]) || check_double(tmp[1]) || check_double(tmp[2]))
	{
		free_args(tmp);
		return (1);
	}
	free_args(tmp);
	return (0);
}