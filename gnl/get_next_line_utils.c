/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:45:04 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 21:42:14 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_callocc(size_t nmemb, size_t size)
{
	char	*new;

	new = malloc(size * nmemb);
	if (!new)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}

size_t	ft_strlenn(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

size_t	ft_strlcpyy(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	src_len;

	i = -1;
	src_len = ft_strlenn(src);
	if (!dst || src[src_len])
		return (src_len);
	while (dstsize-- && src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (src_len);
}

char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	else if (start > ft_strlenn(s))
		return (ft_callocc(1, 1));
	else if (len <= (ft_strlenn(s) - start))
	{
		new = malloc(sizeof(char) * len + 1);
		if (!new)
			return (NULL);
		ft_strlcpyy(new, &s[start], len + 1);
		return (new);
	}
	else
	{
		new = malloc(sizeof(char) * ft_strlenn(s) - start + 1);
		if (!new)
			return (NULL);
		ft_strlcpyy(new, s + start, ft_strlenn(s) + 1);
		free((char *)s);
		return (new);
	}
}
