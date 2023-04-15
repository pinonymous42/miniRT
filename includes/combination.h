/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combination.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:17:39 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 19:54:28 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "color.h"
#include "mlx_info.h"
#include "material.h"
#include "miniRT.h"


typedef struct s_objects
{
	t_fcolor color;
	t_material material;
	t_vec3 vec;
	t_vec3 normal_vec;
	double diameter;
	double height;
	int kind;
	int cylinder_front_or_back;
} t_objects;

typedef struct s_orthonormal
{
	t_vec3 x_unit_vector;
	t_vec3 y_unit_vector;
} t_orthonormal;


int main_loop(t_game *game);
//int main_loop(t_rt *rt);