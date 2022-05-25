/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:20:22 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 03:22:10 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_nb + 1)
	{
		ft_chartable_free(data->cmds[i]->cmd);
		i++;
	}
}

void	temp_free(t_data *data)
{
	if (data->line != NULL)
		free(data->line);
	if (data->token_list != NULL)
		ft_tklstclear(&data->token_list, &free);
	if (data->cmds == NULL)
		free_cmds(data);
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
