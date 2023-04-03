/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:39:58 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 15:15:28 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "util.h"


t_vec3 set_vec3(char *arg)
{
	char **tmp;
	t_vec3 res;

	tmp = ft_split(arg, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		res = vec3_init(0, 0, 0);
		return res;
	}
	res = vec3_init(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
	free_args(tmp);
	return (res);
}
