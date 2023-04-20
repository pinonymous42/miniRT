/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:19:33 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 20:06:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_fcolor
{
	double	red;
	double	green;
	double	blue;
}	t_fcolor;

t_fcolor	rgb_init(int r, int g, int b);
int			rgb_to_int(t_fcolor color);
t_fcolor	add_color(t_fcolor c1, t_fcolor c2, double multi);

#endif