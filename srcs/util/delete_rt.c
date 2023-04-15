/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:41:28 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 14:37:58 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

void delete_rt(t_rt *rt)
{
	t_list *next;
	t_object *tmp;

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
}
