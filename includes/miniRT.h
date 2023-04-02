/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:02:26 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 08:11:54 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft.h"

#define sp 1
#define pl 2
#define cy 3

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct    s_vec3 {
    double     x;
    double     y;
    double     z;
} t_vec3;


//A Ambient lightning
typedef struct s_ambient
{
	double ratio;
	t_color color;
} t_ambient;

//C camera 
typedef struct s_camera
{
	t_vec3 point;
	t_vec3 normalized;
	int fov;
} t_camera;

//L Light 
typedef struct s_light
{
	t_vec3 point;
	double ratio;
	t_color color;
} t_light;

//sp Sphere
typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	t_color color;
} t_sphere;

//pl Plane
typedef struct s_plane
{
	t_vec3 point;
	t_vec3 normalized;
	t_color color;
} t_plane;

//cy Cylinder
typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 normalized;
	double diameter;
	double height;
	t_color color;
} t_cylinder;

typedef struct s_object
{
	void	*object;
	int		type;
} t_object;


typedef struct s_rt
{
	void       *mlx;  // minilibx特有のやつ
    void       *win;  // minilibxのウィンドウを指すポインタ
    int        screen_width;
    int        screen_height;
    t_camera 	*camera;  // カメラのリスト
    t_list      *objects;  // 物体のリスト
    t_ambient    ambient;  // 環境光の強度
    t_light      *light;  // 光源のリスト	
}	t_rt;

#endif
