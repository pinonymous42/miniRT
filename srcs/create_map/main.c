/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/04/02 13:52:58 by tasano           ###   ########.fr       */
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

void delete_rt(t_rt *rt)
{
	t_list *next;

	if (rt->camera)
		free(rt->camera);
	if (rt->light)
		free(rt->light);
	while (rt->objects)
	{
		next = rt->objects->next;
		free(rt->objects->content);
		free(rt->objects);
		rt->objects = next;
	}
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
	init();
	if (create_map(argv[1], &rt))
		exit (1);
	//put_rt(&rt);
	delete_rt(&rt);
	check();
	return (0);
}

__attribute__((destructor))
 static void destructor() {
    system("leaks -q miniRT");
}
