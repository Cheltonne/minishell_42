/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:54:32 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 10:05:13 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	query_user(char *limiter, int *buf_fd)
{
	char	*buf;

	while (1)
	{
		write(1, "> ", 2);
			buf = get_next_line(0, 0);
		if (buf == NULL)
			exit (EXIT_SUCCESS);
		if (ft_strncmp(limiter, buf, ft_strlen(limiter)) == 0)
			break ;
		ft_putstr_fd(buf, *buf_fd);
		free(buf);
	}
	get_next_line(0, 1);
	free(buf);
}
