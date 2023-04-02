#include "miniRT.h"
#include <stdio.h>
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
		printf("color : %d,%d,%d\n", light->color.r, light->color.g, light->color.b);

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
			printf("color : %d,%d,%d\n", sphere->color.r, sphere->color.g, sphere->color.b);
			printf("--------------------------\n");
		}
		else if (object->type == pl)
		{
			plane = (t_plane *)object->object;
			printf("--------- plane ---------\n");
			printf("point : %f,%f,%f\n", plane->point.x, plane->point.y, plane->point.z);
			printf("normalized : %f,%f,%f\n", plane->normalized.x, plane->normalized.y, plane->normalized.z);
			printf("color : %d,%d,%d\n", plane->color.r, plane->color.g, plane->color.b);
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
			printf("color : %d,%d,%d\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
			printf("----------------------------\n");
		}
		rt->objects = rt->objects->next;
	}
}
