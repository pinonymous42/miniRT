//#include "mlx.h"
//#include "combination.h"
#include <stdio.h>
#include <stdlib.h>
#include "miniRT.h"
#include "mlx.h"
#include "mlx_info.h"
#include "key_code.h"
#include "combination.h"
#include "object.h"

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
	t_object *tmp;

	if (rt->camera)
		free(rt->camera);
	if (rt->light)
		free(rt->light);
	while (rt->objects)
	{
		next = rt->objects->next;
		tmp = (t_object *)rt->objects->content;
		free(tmp->object);
		free(rt->objects->content);
		free(rt->objects);
		rt->objects = next;
	}
}

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
		printf("color :%f %f %f\n", light->color.red, light->color.green, light->color.blue);

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
			printf("color : %f %f %f\n", sphere->color.red, sphere->color.green, sphere->color.blue);
			printf("--------------------------\n");
		}
		else if (object->type == pl)
		{
			plane = (t_plane *)object->object;
			printf("--------- plane ---------\n");
			printf("point : %f,%f,%f\n", plane->point.x, plane->point.y, plane->point.z);
			printf("normalized : %f,%f,%f\n", plane->normalized.x, plane->normalized.y, plane->normalized.z);
			printf("color : %f %f %f\n", plane->color.red, plane->color.green, plane->color.blue);
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
			printf("color : %f %f %f\n", cylinder->color.red, cylinder->color.green, cylinder->color.blue);
			printf("----------------------------\n");
		}
		rt->objects = rt->objects->next;
	}
}


int main(int argc, char *argv[])
{
	t_rt rt;

	if (argc != 2)
	{
		ft_putendl_fd("Usage : ./miniRT .rt", 2);
		return (1);
	}
	init_rt(&rt);
	if (create_map(argv[1], &rt))
		exit (1);
	rt.game.mlx = mlx_init();
	rt.game.win = mlx_new_window(rt.game.mlx, WIDTH, HEIGHT, "miniRT");
	mlx_hook(rt.game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &rt.game);
	mlx_hook(rt.game.win, X_EVENT_KEY_EXIT, 1, &window_close, &rt.game);
	//main_loop(&rt.game);
	draw_miniRT(&rt);
	mlx_loop(rt.game.mlx);
	
	delete_rt(&rt);
	return (0);
}

//__attribute__((destructor))
// static void destructor() {
//    system("leaks -q miniRT");
//}
