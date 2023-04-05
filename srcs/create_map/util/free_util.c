/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:10:36 by tasano            #+#    #+#             */
/*   Updated: 2023/04/03 15:53:40 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
