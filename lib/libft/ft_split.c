/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:18:42 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/03/30 06:08:28 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_get_size(char const *s, char c);
char	**ft_free_all(char **res, size_t size);
char	**ft_s_cpy(char **res, char const	*s, char c, size_t res_size);

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	res_s;

	if (!s)
		return (NULL);
	res_s = ft_get_size(s, c);
	res = (char **)malloc((res_s + 1) * sizeof(char **));
	if (!res)
		return (NULL);
	return (ft_s_cpy(res, s, c, res_s));
}

char	**ft_s_cpy(char **res, char const *s, char c, size_t res_size)
{
	size_t	index;
	size_t	len;

	index = 0;
	while (*s && index < res_size)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (s[len] && s[len] != c)
			len++;
		if (len != 0)
		{
			res[index] = ft_substr(s, 0, len);
			if (!res[index])
				return (ft_free_all(&res[index], index));
			index++;
		}
		s += len;
	}
	res[index] = NULL;
	return (res);
}

char	**ft_free_all(char **res, size_t size)
{
	while (size)
	{
		free(res[size]);
		size --;
	}
	free(res);
	return (NULL);
}

size_t	ft_get_size(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i]&& s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}
