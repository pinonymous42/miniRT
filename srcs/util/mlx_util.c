/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:24:27 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 11:27:54 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		deal_key(int key_code, t_game *game)
{
	(void)game;
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}

int 	window_close(t_game *game)
{
	(void)game;
		exit(0);
}

