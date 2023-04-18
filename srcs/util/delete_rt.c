/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:41:28 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:09:44 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "mlx.h"

void	delete_rt(t_rt *rt)
{
	t_list		*next;
	t_object	*tmp;

	free(rt->camera);
	free(rt->light);
	free(rt->ambient);
	while (rt->objects)
	{
		next = rt->objects->next;
		tmp = (t_object *)rt->objects->content;
		free(tmp->object);
		free(tmp);
		free(rt->objects);
		rt->objects = next;
	}
	if (rt->game.mlx)
		mlx_destroy_window(rt->game.mlx, rt->game.win);
}
