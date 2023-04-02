/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:24 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 13:48:01 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_map.h"





#include "miniRT.h"

t_fcolor set_color(char *arg)
{
	char **tmp;
	t_fcolor res;

	tmp = ft_split(arg, ',');
	res.red = -1;
	res.green = -1;
	res.blue = -1;
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		return res;
	}
	res.red = ft_atoi(tmp[0]);
	res.green = ft_atoi(tmp[1]);
	res.blue = ft_atoi(tmp[2]);
	free_args(tmp);
	return (res);
}
