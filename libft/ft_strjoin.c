/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:23:41 by chajax            #+#    #+#             */
/*   Updated: 2022/05/16 21:04:49 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		o;
	int		total_len;
	char	*new;

	i = 0;
	o = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = malloc(sizeof(char) * total_len);
	if (!new)
		return (NULL);
	while (s1[i])
		new[o++] = s1[i++];
	i = 0;
	while (s2[i])
		new[o++] = s2[i++];
	new[o] = '\0';
	return (new);
}
