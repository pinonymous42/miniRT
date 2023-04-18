/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:24:27 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 22:12:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code.h"
#include "mlx_info.h"
#include "util.h"
#include "miniRT.h"
#include "mlx.h"

int	deal_key(int key_code, t_rt *rt)
{
	if (key_code == KEY_ESC)
	{
		delete_rt(rt);
		exit(0);
	}
	return (0);
}

int	window_close(t_rt *rt)
{
	delete_rt(rt);
	exit(0);
}

int	init_hooks(t_rt *rt)
{
	mlx_hook(rt->game.win, X_EVENT_KEY_PRESS, 1, &deal_key, rt);
	mlx_hook(rt->game.win, X_EVENT_KEY_EXIT, 1, &window_close, rt);
	return (0);
}

int	init_mlx(t_rt *rt)
{
	rt->game.mlx = mlx_init();
	rt->game.win = mlx_new_window(rt->game.mlx, WIDTH, HEIGHT, "miniRT");
	return (0);
}
