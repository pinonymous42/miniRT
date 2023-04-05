/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/04/03 16:33:07 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "miniRT.h"
#include <fcntl.h>

void put_rt(t_rt *rt)
{
	t_camera *camera;
	printf("\n------------------ camera ------------------\n");
		camera = (t_camera *)rt->camera;
		printf("fov : %d\n", camera->fov);
		printf("point : %f,%f,%f\n", camera->point.x, camera->point.y, camera->point.z);
		printf("way : %f,%f,%f\n", camera->normalized.x, camera->normalized.y, camera->normalized.z);
	printf("\n------------------ light ------------------\n");
	t_light *light;

		light = (t_light *)rt->light;
		printf("point : %f,%f,%f\n", light->point.x, light->point.y, light->point.z);
		printf("radio : %f\n", light->ratio);
		printf("color : %d,%d,%d\n", light->color.red, light->color.green, light->color.blue);

	printf("------------------ object ------------------\n");
	t_sphere *sphere;
	t_plane *plane;
	t_cylinder *cylinder;
	t_object *object;
	while (rt->objects)
	{
		object = (t_object *)rt->objects->content;
		if (object->type == sp)
		{
			sphere = (t_sphere *)object->object;
			printf("--------- sphere ---------\n");
			printf("center : %f,%f,%f\n", sphere->center.x, sphere->center.y, sphere->center.z);
			printf("diameter : %f\n", sphere->diameter);
			printf("color : %d,%d,%d\n", sphere->color.red, sphere->color.green, sphere->color.blue);
			printf("--------------------------\n");
		}
		else if (object->type == pl)
		{
			plane = (t_plane *)object->object;
			printf("--------- plane ---------\n");
			printf("point : %f,%f,%f\n", plane->point.x, plane->point.y, plane->point.z);
			printf("normalized : %f,%f,%f\n", plane->normalized.x, plane->normalized.y, plane->normalized.z);
			printf("color : %d,%d,%d\n", plane->color.red, plane->color.green, plane->color.blue);
			printf("--------------------------\n");
		}
		else if (object->type == cy)
		{
			cylinder = (t_cylinder *)object->object;
			printf("--------- cylinder ---------\n");
			printf("center : %f,%f,%f\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
			printf("normalized : %f,%f,%f\n", cylinder->normalized.x, cylinder->normalized.y, cylinder->normalized.z);
			printf("diameter : %f\n", cylinder->diameter);
			printf("height : %f\n", cylinder->height);
			printf("color : %d,%d,%d\n", cylinder->color.red, cylinder->color.green, cylinder->color.blue);
			printf("----------------------------\n");
		}
		rt->objects = rt->objects->next;
	}
}



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

	init_rt(&rt);
	//init();
	if (create_map(argv[1], &rt))
		exit (1);
	put_rt(&rt);
	delete_rt(&rt);
	//check();
	return (0);
}

//__attribute__((destructor))
// static void destructor() {
//    system("leaks -q miniRT");
//}
