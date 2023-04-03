/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:28:38 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 14:29:30 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>
//色系
t_fcolor	rgb_init(int r, int g, int b)
{
	t_fcolor ret;

	ret.red = r;
	ret.green = g;
	ret.blue = b;
	return (ret);
}

int	rgb_to_int(int r, int g, int b)//rgbを16進数のやつに変化(R, G, B) = (255, 0, 0)ならば0xFF0000(256*256*255 + 256 * 0 + 0)へ
{
	return ((int)(r * pow(256, 2) + g * pow(256, 1) + b));
}

t_fcolor	add_color(t_fcolor c1, t_fcolor c2, double multi)
{
	t_fcolor	ret;

	ret.red = c1.red + c2.red * multi;
	if (ret.red > 255)
		ret.red = 255;
	else if (ret.red < 0)
		ret.red = 0;
	ret.green = c1.green + c2.green * multi;
	if (ret.green > 255)
		ret.green = 255;
	else if (ret.green < 0)
		ret.green = 0;
	ret.blue = c1.blue + c2.blue * multi;
	if (ret.blue > 255)
		ret.blue = 255;
	else if (ret.green < 0)
		ret.green = 0;
	return (ret);
}
