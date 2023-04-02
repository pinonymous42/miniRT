/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:42:22 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 11:56:03 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INFO_H
#define	MLX_INFO_H

#define WIDTH 512
#define HEIGHT 512

#define NUMBER 6

#define SPHERE 1
#define PLAIN 2
#define CYLINDER 3

#define NOTHING 0
#define FRONT 1
#define BACK 2

typedef struct	s_game
{
	void	*mlx;
	void	*win;
}				t_game;

#endif