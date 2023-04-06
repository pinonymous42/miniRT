/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:10:36 by tasano            #+#    #+#             */
/*   Updated: 2023/04/04 18:42:33 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void free_args(char **args)
{
	size_t i;

	i = 0;
	if (!args)
		return;
	while (args[i])
		free(args[i++]);
	free(args);
}
