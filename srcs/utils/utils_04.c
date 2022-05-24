/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_04.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:43:40 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 01:22:34 by chajax           ###   ########.fr       */
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

void	init_env(t_data *data, char **envp)
{
	data->env = seteup_env(data, envp);
	data->env_arr = dupenv(data->env);
	g_exit = 0;
}
