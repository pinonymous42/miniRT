/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:38:07 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 13:56:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "object.h"

int set_list(t_rt *rt, void *content, int type)
{
	t_object	*object;
	t_list		*new;

	object = (t_object *)malloc(sizeof(t_object));
	if (!object)
		return (1);
	object->object = content;
	object->type  = type;
	object->t = 0;
	new = ft_lstnew((void *)object);
	if (!new)
	{
		free (object);
		return (1);
	}
	ft_lstadd_back(&rt->objects, new);
	return (0);
}