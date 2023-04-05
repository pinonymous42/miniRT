/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:02:26 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 16:01:38 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "libft.h"
#include "vector.h"
#include "color.h"
#include "object.h"
#include "mlx_info.h"

// A Ambient lightning
typedef struct s_ambient
{
	double ratio;
	t_fcolor color;
} t_ambient;

// C camera
typedef struct s_camera
{
	t_vec3 point;
	t_vec3 normalized;
	int fov;
} t_camera;

// L Light
typedef struct s_light
{
	t_vec3 point;
	double ratio;
	t_fcolor color;
} t_light;

typedef struct s_rt
{
	t_game game;
	int screen_width;
	int screen_height;
	t_camera *camera;  // カメラのリスト
	t_list *objects;   // 物体のリスト
	t_ambient ambient; // 環境光の強度
	t_light *light;	   // 光源のリスト
} t_rt;

int create_map(char *filename, t_rt *rt);

#endif
