/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:25:57 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 16:55:49 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int check_color(t_color color)
{
	if (color.r < 0 || 255 < color.r)
		return (1);
	if (color.g < 0 || 255 < color.g)
		return (1);
	if (color.b < 0 || 255 < color.b)
		return (1);
	return (0);
}