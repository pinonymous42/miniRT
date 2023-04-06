/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:37:26 by tasano            #+#    #+#             */
/*   Updated: 2023/04/05 17:16:13 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "create_map.h"
#include <stdio.h>
#include <fcntl.h>

static int set_element(char **elements, t_rt *rt)
{
	int status;

	status = 0;
	if (ft_strncmp("A", elements[0], 2) == 0)
		status = set_ambient(++elements, rt);
	else if (ft_strncmp("L", elements[0], 2) == 0)
		status = set_light(++elements, rt);
	else if (ft_strncmp("C", elements[0], 2) == 0)
		status = set_camera(++elements, rt);
	else if (ft_strncmp("sp", elements[0], 2) == 0)
		status = set_object(elements, rt);
	else if (ft_strncmp("pl", elements[0], 2) == 0)
		status = set_object(elements, rt);
	else if (ft_strncmp("cy", elements[0], 2) == 0)
		status = set_object(elements, rt);
	return (status);
}

static int parse_map(int fd, t_rt *rt)
{
	char *line;
	char **elements;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line && *line == '\n')
			continue;
		elements = ft_split_space(line);
		free(line);
		if (!elements)
			return (1);
		if (set_element(elements, rt))
			return (1);
		free_args(elements);
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
	if (parse_map(fd, rt))
	{
		ft_putendl_fd("ERROR", 2);
		// delete_rt(rt);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
