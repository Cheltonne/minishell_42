/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:20:22 by chajax            #+#    #+#             */
/*   Updated: 2022/05/24 22:34:46 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmds(t_data *data)
{
	int	i;
	int	o;

	i = 0;
	while (i < data->pipe_nb + 1)
	{
		o = 0;
		while (o < ft_table_count((void **)data->cmds[i]->cmd))
		{
			free(data->cmds[i]->cmd[o]);
			o++;
		}
		free(data->cmds[i]->cmd);
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);
}

void	temp_free(t_data *data)
{
	free(data->line);
	ft_tklstclear(&data->token_list, &free);
	if (data->cmds != NULL)
		free_cmds(data);
	unlink(".here_doc");
}

void	free_everything(t_data *data)
{
	temp_free(data);
	free_env(data->env);
	free(data->env_arr);
	free(data);
}

void	dual_free(void **ptr, void **ptr2)
{
	free((*ptr));
	free((*ptr2));
}
