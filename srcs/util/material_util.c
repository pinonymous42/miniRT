/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:56:45 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 11:56:49 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//material系
t_material material_init(double kDif, double kSpe, double shininess)
{
	t_material ret;

	ret.kDif = kDif;
	ret.kSpe = kSpe;
	ret.shininess = shininess;
	return (ret);
}
