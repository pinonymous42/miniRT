/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/04/01 18:14:35 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "miniRT.h"
#include <fcntl.h>


void init_rt(t_rt *rt)
{
	rt->screen_width = 1000;
	rt->screen_height = 800;
	rt->camera = NULL;
	rt->objects = NULL;
	rt->light = NULL;
}

int main(int argc, char *argv[])
{
	t_rt rt;

	if (argc != 2)
	{
		ft_putendl_fd("Usage : ./miniRT fail.rt", 2);
		return (1);
	}
	init_rt(&rt);
	if (create_map(argv[1], &rt))
		exit (1);
	put_rt(&rt);
	return (0);
}

//__attribute__((destructor))
// static void destructor() {
//    system("leaks -q miniRT");
//}
