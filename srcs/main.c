/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:53 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 22:18:45 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"

void	init_rt(t_rt *rt)
{
	rt->game.mlx = NULL;
	rt->game.win = NULL;
	rt->camera = NULL;
	rt->objects = NULL;
	rt->light = NULL;
	rt->ambient = NULL;
	rt->min_object = NULL;
	rt->min = 0;
	rt->epsilon = 1.0 / 512;
}

int	check_rtfile(char *file)
{
	size_t	len;

	if (!file || !file[0])
		return (1);
	len = ft_strlen(file);
	if (len < 3)
		return (1);
	len -= 3;
	file += len;
	if (ft_strncmp(file, ".rt", 4) == 0)
		return (0);
	else
		return (1);
}

int	main(int argc, char *argv[])
{
	t_rt	rt;
	int		status;

	if (argc != 2 || check_rtfile(argv[1]))
	{
		ft_putendl_fd("Usage : ./miniRT .rt", 2);
		return (1);
	}
	init_rt(&rt);
	status = create_map(argv[1], &rt);
	if (status)
		return (status);
	init_mlx(&rt);
	draw_minirt(&rt);
	init_hooks(&rt);
	mlx_loop(rt.game.mlx);
	return (0);
}
