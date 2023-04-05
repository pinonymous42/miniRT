/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:19:33 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 16:11:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
#define COLOR_H

typedef struct s_fcolor {
    int     red;
    int     green;
    int     blue;
}               t_fcolor;

t_fcolor	rgb_init(int r, int g, int b);
int	rgb_to_int(int r, int g, int b);
t_fcolor	add_color(t_fcolor c1, t_fcolor c2, double multi);

#endif