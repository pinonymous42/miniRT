/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:42:22 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 20:00:34 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INFO_H
# define MLX_INFO_H

# define WIDTH 512
# define HEIGHT 512

# include "miniRT.h"

int	deal_key(int key_code, t_rt	*rt);
int	window_close(t_rt *rt);

#endif