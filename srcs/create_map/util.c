/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:02:07 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 14:24:56 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void free_args(char **args)
{
	if (!args)
		return;
	while (*args)
	{
		if (*args)
			free(*args);
		*args = NULL;
		args++;
	}
	args = NULL;
}

int ft_isdouble(char c)
{
	return (ft_isdigit(c) || c == '.');
}

int check_double(char *str)
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