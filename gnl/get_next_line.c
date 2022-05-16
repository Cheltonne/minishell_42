/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:52:06 by chajax            #+#    #+#             */
/*   Updated: 2022/02/25 21:00:58 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinn(char *s1, char *s2)
{
	int		i;
	int		o;
	int		total_len;
	char	*new;

	i = 0;
	o = 0;
	total_len = ft_strlenn(s1) + ft_strlenn(s2) + 1;
	new = malloc(sizeof(char) * total_len);
	if (!new)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			new[o++] = s1[i++];
		free((char *)s1);
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			new[o++] = s2[i++];
		new[o] = '\0';
	}
	return (new);
}

void	free_exp(char	**str)
{
	if (!*str)
		return ;
	free(*str);
	*str = NULL;
}

char	*check_eof(char *local, char **export, char *buf)
{
	free(buf);
	if (*export)
	{
		if (**export != '\0')
		{
			local = ft_strjoinn(local, *export);
			free_exp(export);
			return (local);
		}
	}
	free_exp(export);
	return (NULL);
}

int	find_backline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd, int last)
{
	int				ret;
	char			*buf;
	char			*local;
	static char		*export[1024];

	if (last)
	{
		gnl_helper(fd, export);
		return (NULL);
	}
	local = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	while (find_backline(export[fd]) == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 1)
			return (check_eof(local, &export[fd], buf));
		buf[ret] = '\0';
		export[fd] = ft_strjoinn(export[fd], buf);
	}
	local = ft_substrr(export[fd], 0, find_backline(export[fd]) + 1);
	export[fd] = ft_substrr(export[fd], find_backline(export[fd]) + 1,
			ft_strlenn(export[fd]) - find_backline(export[fd]));
	free(buf);
	return (local);
}
