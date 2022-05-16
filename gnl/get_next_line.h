/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:48:54 by chajax            #+#    #+#             */
/*   Updated: 2022/05/16 21:08:14 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 9999 
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

void	*ft_callocc(size_t nmemb, size_t size);
char	*ft_strjoinn(char *s1, char *s2);
size_t	ft_strlenn(const char *str);
size_t	ft_strlcpyy(char *dst, const char *src, size_t dstsize);
char	*ft_substrr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd, int free);
int		find_backline(char *str);
void	free_exp(char **str);
void	gnl_helper(int fd, char **export);
#endif
