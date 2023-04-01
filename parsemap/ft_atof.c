/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:45:33 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 17:17:44 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double ft_atof(char *str)
{
	int sign;
	double res;
	double digit;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if ((*str == '+' || *str == '-'))
		sign = 44 - *str++;
	res = 0;
	while (*str && ft_isdigit(*str))
		res = (res * 10) + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		digit = 1;
		while (*str && ft_isdigit(*str))
		{
			digit *= 0.1;
			res += (*str++ - '0') * digit;
		}
	}
	return (res * sign);
}
