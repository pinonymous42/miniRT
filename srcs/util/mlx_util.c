/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:24:27 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:09:27 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_code.h"
#include "mlx_info.h"
#include "util.h"
#include "miniRT.h"

int	deal_key(int key_code, t_rt *rt)
{
	if (key_code == KEY_ESC)
	{
		delete_rt(rt);
		exit(0);
	}
	return (0);
}

int	window_close(t_rt *rt)
{
	delete_rt(rt);
	exit(0);
}
