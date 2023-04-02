/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 06:09:05 by tasano            #+#    #+#             */
/*   Updated: 2023/03/30 07:36:37 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_space_get_size(char const *s);
char	**ft_space_free_all(char **res, size_t size);
char	**ft_space_s_cpy(char **res, char const	*s, size_t res_size);

char	**ft_split_space(char const *s)
{
	char	**res;
	size_t	res_s;

	if (!s)
		return (NULL);
	res_s = ft_space_get_size(s);
	res = (char **)malloc((res_s + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_space_s_cpy(res, s, res_s));
}

char	**ft_space_s_cpy(char **res, char const *s, size_t res_size)
{
	size_t	index;
	size_t	len;

	index = 0;
	while (*s && index < res_size)
	{
		len = 0;
		while (*s && ft_isspace(*s))
			s++;
		while (s[len] && !ft_isspace(s[len]))
			len++;
		if (len != 0)
		{
			res[index] = ft_substr(s, 0, len);
			if (!res[index])
				return (ft_space_free_all(&res[index], index));
			index++;
		}
		s += len;
	}
	res[index] = NULL;
	return (res);
}

char	**ft_space_free_all(char **res, size_t size)
{
	while (size)
	{
		free(res[size]);
		size --;
	}
	free(res);
	return (NULL);
}

size_t	ft_space_get_size(char const *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			count++;
			while (*s && !ft_isspace(*s))
				s++;
		}
	}
	return (count);
}
