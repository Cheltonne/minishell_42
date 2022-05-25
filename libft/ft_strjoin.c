/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:35:38 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 16:35:41 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int to_free)
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
	if (to_free == 1)
		free(s1);
	i = 0;
	while (s2[i])
		new[o++] = s2[i++];
	if (to_free == 2)
		free(s2);
	new[o] = '\0';
	return (new);
}
