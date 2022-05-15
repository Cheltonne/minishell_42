/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:40:59 by chajax            #+#    #+#             */
/*   Updated: 2022/05/15 16:15:48 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_finder(t_tklist **i)
{
	while ((*i)->type != END || (*i)->type != PIPE)
		(*i) = (*i)->next;
}

int	pipe_count(char *str)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '|')
			ret++;
		i++;
	}
	return (ret);
}

void	exec_single_cmd(t_data *data)
{
	fork_wrapper(&data->id);
	if (data->id == 0)
	{
		if (data->cmds[0]->in != 0 || data->cmds[0]->out != 1)
		{
			dup2(data->cmds[0]->in, STDIN_FILENO);
			dup2(data->cmds[0]->out, STDOUT_FILENO);
		}
		execute(data->cmds[0]->cmd, data->env_arr);
	}
}
