/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:54:32 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 10:34:07 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	query_user(char *limiter, int *buf_fd)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (buf == NULL)
			exit (EXIT_SUCCESS);
		if (ft_strncmp(limiter, buf, ft_strlen(limiter) + ft_strlen(buf)) == 0)
			break ;
		buf = ft_strjoin(buf, "\n", 1);
		ft_putstr_fd(buf, *buf_fd);
		free(buf);
	}
	free(buf);
}
