/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:40:44 by tasano            #+#    #+#             */
/*   Updated: 2023/03/31 20:40:50 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int set_ambient(char **argv, t_rt *rt)
{
	if (!argv || !argv[0] || !argv[1])
		return (1);
	rt->ambient.ratio = ft_atoi(argv[0]);
	rt->ambient.color = set_color(argv[1]);
	return (0);
}
