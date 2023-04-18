
#include <stdio.h>
#include <stdlib.h>
#include "miniRT.h"
#include "mlx.h"
#include "mlx_info.h"
#include "key_code.h"
#include "object.h"
#include "util.h"

void init_rt(t_rt *rt)
{
	rt->game.mlx = NULL;
	rt->game.win = NULL;
	rt->camera = NULL;
	rt->objects = NULL;
	rt->light = NULL;
	rt->ambient = NULL;
}

int init_hooks(t_rt *rt)
{
	mlx_hook(rt->game.win, X_EVENT_KEY_PRESS, 1, &deal_key, rt);
	mlx_hook(rt->game.win, X_EVENT_KEY_EXIT, 1, &window_close, rt);
	return (0);
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
	int status = create_map(argv[1], &rt);
	if (status)
		return (status);
	rt.game.mlx = mlx_init();
	rt.game.win = mlx_new_window(rt.game.mlx, WIDTH, HEIGHT, "miniRT");
	draw_miniRT(&rt);
	// main_loop(&rt.game);
	init_hooks(&rt);
	mlx_loop(rt.game.mlx);
	delete_rt(&rt);
	return (status);
}

__attribute__((destructor))
 static void destructor() {
    system("leaks -q miniRT");
}
