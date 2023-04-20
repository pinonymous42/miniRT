/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:37:26 by tasano            #+#    #+#             */
/*   Updated: 2023/04/18 15:05:41 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "create_map.h"
#include <stdio.h>
#include <fcntl.h>
#include "util.h"

static void	put_cratemap_err(int status)
{
	ft_putstr_fd("ERROR status = ", 2);
	ft_putnbr_fd(status, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("Please see ./includes/create_map_err.h", 2);
}

static int	set_element(char **elements, t_rt *rt)
{
	if (ft_strncmp("A", elements[0], 2) == 0)
		return (set_ambient(++elements, rt));
	else if (ft_strncmp("L", elements[0], 2) == 0)
		return (set_light(++elements, rt));
	else if (ft_strncmp("C", elements[0], 2) == 0)
		return (set_camera(++elements, rt));
	else if (ft_strncmp("sp", elements[0], 2) == 0)
		return (set_sphere(rt, ++elements));
	else if (ft_strncmp("pl", elements[0], 2) == 0)
		return (set_plane(rt, ++elements));
	else if (ft_strncmp("cy", elements[0], 2) == 0)
		return (set_cylinder(rt, ++elements));
	else
		return (NON_ELEM_ERR);
	return (0);
}

static int	check_none_elem(t_rt *rt)
{
	if (!rt->ambient)
		return (A_NONE_ERR);
	if (!rt->camera)
		return (C_NONE_ERR);
	if (!rt->light)
		return (L_NONE_ERR);
	if (!rt->objects)
		return (OBJECT_NONE_ERR);
	return (0);
}

static int	parse_map(int fd, t_rt *rt)
{
	char	*line;
	char	**elements;
	int		status;

	status = 0;
	while (1 && status == 0)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line && *line == '\n')
			continue ;
		elements = ft_split_space(line);
		free(line);
		if (!elements)
			return (MALLOC_ERR);
		status = set_element(elements, rt);
		free_args(elements);
	}
	if (status == 0)
		status = check_none_elem(rt);
	return (status);
}

int	create_map(char *filename, t_rt *rt)
{
	int	fd;
	int	status;

	fd = open(filename, R_OK);
	if (fd < 0)
	{
		perror("miniRT");
		return (1);
	}
	status = parse_map(fd, rt);
	if (status)
	{
		delete_rt(rt);
		put_cratemap_err(status);
	}
	close(fd);
	return (status);
}
