/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_vec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:57:56 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:58:29 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIR_VEC_H
#define DIR_VEC_H

#include "vector.h"
typedef struct s_orthonormal
{
	t_vec3 x_unit_vector;
	t_vec3 y_unit_vector;
} t_orthonormal;

#endif