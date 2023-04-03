/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:42:22 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 17:37:34 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INFO_H
#define	MLX_INFO_H

#define WIDTH 512
#define HEIGHT 512

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

int		deal_key(int key_code, t_game *game);
int 	window_close(t_game *game);

#endif