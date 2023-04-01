/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:39:58 by tasano            #+#    #+#             */
/*   Updated: 2023/03/31 20:40:14 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 set_vec3(char *arg)
{
	char **tmp;
	t_vec3 res;

	tmp = ft_split(arg, ',');
	// if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	//	return res;
	res.x = atof(tmp[0]);
	res.y = atof(tmp[1]);
	res.z = atof(tmp[2]);
	free_args(tmp);
	return (res);
}
