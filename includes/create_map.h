/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:11:58 by tasano            #+#    #+#             */
/*   Updated: 2023/04/15 14:35:11 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_MAP_H
#define CREATE_MAP_H

#include "color.h"
#include "vector.h"
#include "util.h"
#include "miniRT.h"
#include "create_map_errno.h"
//test
void put_rt(t_rt *rt);

//input file && create struct
t_fcolor set_color(char *arg);
t_vec3 set_vec3(char *arg);
int set_object(char **elements, t_rt *rt);
int set_ambient(char **argv, t_rt *rt);
int set_camera(char **argv, t_rt *rt);
int set_light(char **argv, t_rt *rt);
int create_map(char *filename, t_rt *rt);

int set_sphere(t_rt *rt, char **argv);
int set_plane(t_rt *rt, char **argv);
int set_cylinder(t_rt *rt ,char **argv);
int set_list(t_rt *rt, void *content, int type);

//checker
int check_vec(char *vec_str);
int check_vec_range(t_vec3 vec, double min, double max);
int check_color(t_fcolor color);

//util
void free_args(char **args);
int ft_isdouble(char c);
int check_double(char *str);

#endif