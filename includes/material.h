/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:22:16 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 19:58:09 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# define KDIF        0.69
# define KSPE        0.3
# define SHININESS   8

typedef struct s_material_val
{
	double	diffusion;
	double	speclar;
}	t_material_val;

#endif