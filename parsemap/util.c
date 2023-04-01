/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:02:07 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 14:05:39 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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