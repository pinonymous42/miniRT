//#include "mlx.h"
//#include "combination.h"
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include "mlx_info.h"
#include "key_code.h"
#include "combination.h"


typedef struct s_test
{
	int val;
} t_test;

void test_func(t_test *test)
{
	for (int i=0; i<3;i++)
		test[i].val = 10;
}


int main(void)
{

	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "miniRT");
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 1, &window_close, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}