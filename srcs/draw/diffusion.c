/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:40:42 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 19:10:22 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "vector.h"
#include "object.h"
#include "material.h"

double	diffusion(t_vec3 incident, t_vec3 reflect)
{
	double	dot_1;

	dot_1 = vec3_dot(incident, reflect);
	if (dot_1 <= 0)
		dot_1 = 0;
	return (dot_1 * KDIF);
}
