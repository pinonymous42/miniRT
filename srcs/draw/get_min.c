/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:40:16 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 18:56:35 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "miniRT.h"

static t_object	*check_obj(t_list *lst)
{
	t_object	*min_object;
	t_object	*object;
	t_list		*head;

	head = lst;
	while (lst)
	{
		object = (t_object *)lst->content;
		if (object->t != 0)
		{
			min_object = object;
			break ;
		}
		min_object = (t_object *)head->content;
		min_object->t = 0;
		lst = lst->next;
	}
	return (min_object);
}

t_object	*get_min_object(t_list *lst)
{
	t_object	*object;
	t_object	*min_object;

	min_object = check_obj(lst);
	if (min_object->t != 0)
	{
		while (lst)
		{
			object = (t_object *)lst->content;
			if (object->t != 0 && object->t < min_object->t)
				min_object = object;
			lst = lst->next;
		}
	}
	return (min_object);
}

int	get_min(t_rt *rt)
{
	rt->min_object = get_min_object(rt->objects);
	rt->min = rt->min_object->t;
	return (0);
}
