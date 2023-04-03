/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:24 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 15:14:06 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "color.h"
#include "util.h"

t_fcolor set_color(char *arg)
{
	char **tmp;
	t_fcolor res;

	tmp = ft_split(arg, ',');
	rgb_init(-1, -1, -1);
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		return res;
	}
	rgb_init(ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	free_args(tmp);
	return (res);
}
