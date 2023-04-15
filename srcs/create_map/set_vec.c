/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:39:58 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 15:02:15 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "util.h"

static int	ft_isdouble(char c)
{
	return (ft_isdigit(c) || c == '.');
}

static int	check_double(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdouble(*str))
			return (1);
		str++;
	}
	return (0);
}

int	check_vec_range(t_vec3 vec, double min, double max)
{
	if (vec.x < min || max < vec.x)
		return (1);
	if (vec.y < min || max < vec.y)
		return (1);
	if (vec.z < min || max < vec.z)
		return (1);
	return (0);
}

int	check_vec(char *vec_str)
{
	char	**tmp;

	tmp = ft_split(vec_str, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		return (1);
	}
	if (check_double(tmp[0]) || check_double(tmp[1]) || check_double(tmp[2]))
	{
		free_args(tmp);
		return (1);
	}
	free_args(tmp);
	return (0);
}

t_vec3	set_vec3(char *arg)
{
	char	**tmp;
	t_vec3	res;

	tmp = ft_split(arg, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
	{
		free_args(tmp);
		res = vec3_init(0, 0, 0);
		return (res);
	}
	res = vec3_init(ft_atof(tmp[0]), ft_atof(tmp[1]), ft_atof(tmp[2]));
	free_args(tmp);
	return (res);
}
