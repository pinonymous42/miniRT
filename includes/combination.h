/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combination.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:17:39 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 14:49:17 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "color.h"
#include "mlx_info.h"
#include "material.h"
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

void get_t_value(t_vec3 start_vec, t_vec3 dir_vec, t_objects *object_list, double *t, int i);
int deal_key(int key_code, t_game *game);
int window_close(t_game *game);

int main_loop(t_game *game);