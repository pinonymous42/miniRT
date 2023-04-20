/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:02:26 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 22:15:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vector.h"
# include "color.h"
# include "object.h"

// A Ambient lightning
typedef struct s_ambient
{
	double		ratio;
	t_fcolor	color;
}	t_ambient;

// C camera
typedef struct s_camera
{
	t_vec3	point;
	t_vec3	normalized;
	double	fov;
}	t_camera;

// L Light
typedef struct s_light
{
	t_vec3		point;
	double		ratio;
	t_fcolor	color;
}	t_light;

typedef struct s_game
{
	void	*mlx;
	void	*win;
}	t_game;

typedef struct s_rt
{
	t_game		game;
	t_camera	*camera;
	t_list		*objects;
	t_ambient	*ambient;
	t_light		*light;
	t_object	*min_object;
	double		min;
	double		epsilon;
}	t_rt;

int	init_hooks(t_rt *rt);
int	init_mlx(t_rt *rt);
int	create_map(char *filename, t_rt *rt);
int	draw_minirt(t_rt *rt);
#endif
