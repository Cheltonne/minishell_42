/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:20:22 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 16:28:10 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmds == NULL)
		return ;
	while (i < data->pipe_nb + 1)
	{
		if (data->cmds[i] != NULL)
		{
			ft_chartable_free(data->cmds[i]->cmd);
			free(data->cmds[i]);
		}
		i++;
	}
	if (data->cmds)
		free(data->cmds);
	data->cmds = NULL;
}

void	temp_free(t_data *data)
{
	if (data->line != NULL)
		free(data->line);
	if (data->token_list != NULL)
	{
		while (data->token_list->prev != NULL)
			data->token_list = data->token_list->prev;
		ft_tklstclear(&data->token_list, &free);
	}
	if (data->cmds != NULL)
	{
		free_cmds(data);
	}
	unlink(".here_doc");
}

void	free_everything(t_data *data)
{
	temp_free(data);
	if (data->env != NULL)
		free_env(data->env);
	if (*data->env_arr != NULL)
		free(data->env_arr);
	free(data);
}

void	dual_free(void **ptr, void **ptr2)
{
	free((*ptr));
	free((*ptr2));
}

int	cmds_null_exit(t_data *data)
{
	temp_free(data);
	return (FAILURE);
}
