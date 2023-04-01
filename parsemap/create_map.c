/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:37:26 by tasano            #+#    #+#             */
/*   Updated: 2023/04/01 14:04:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <fcntl.h>

static int set_element(char **elements, t_rt *rt)
{

	if (ft_strncmp("A", elements[0], 2) == 0)
		set_ambient(++elements, rt);
	else if (ft_strncmp("L", elements[0], 2) == 0)
		set_light(++elements, rt);
	else if (ft_strncmp("C", elements[0], 2) == 0)
		set_camera(++elements, rt);
	else if (ft_strncmp("sp", elements[0], 2) == 0)
		set_object(elements, rt);
	else if (ft_strncmp("pl", elements[0], 2) == 0)
		set_object(elements, rt);
	else if (ft_strncmp("cy", elements[0], 2) == 0)
		set_object(elements, rt);
	return (0);
}

static int parse_map(int fd, t_rt *rt)
{
	char *line;
	char **elements;

	line = get_next_line(fd);
	while (line)
	{
		if (*line && *line == '\n')
		{
			line = get_next_line(fd);
			continue;
		}
		elements = ft_split_space(line);
		free(line);
		if (!elements)
			return (1);
		set_element(elements, rt);
		free_args(elements);
		line = get_next_line(fd);
	}
	return (0);
}

int create_map(char *filename, t_rt *rt)
{
	int fd;
	fd = open(filename, R_OK);
	if (fd < 0)
	{
		perror("miniRT");
		return (1);
	}
	parse_map(fd, rt);
	close(fd);
	return (0);
}
