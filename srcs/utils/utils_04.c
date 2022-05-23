/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_04.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:43:40 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 14:15:44 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_wrapper(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_nb + 1)
	{
		waitpid(data->cmds[i]->id, &g_exit, 0);
		i++;
	}
}

int	ad(int *value)
{
	(*value) += 1;
	return (SUCCESS);
}
