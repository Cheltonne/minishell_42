/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:47:47 by chajax            #+#    #+#             */
/*   Updated: 2022/05/19 13:52:01 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fork_wrapper(pid_t *child)
{
	*child = fork();
	if (*child < 0)
		(perror("Fork"));
}

int spawn_proc (int in, int out, t_data *data, char **cmd)
{
	fork_wrapper(&data->id);
	if (data->id == CHILD)
	{
		if (in != STDIN_FILENO)
        {
        	dup2(in, STDIN_FILENO);
        	close(in);
        }
    	if (out != STDOUT_FILENO)
        {
        	dup2(out, STDOUT_FILENO);
        	close(out);
        }
		execute(cmd, data->env_arr);
    }
	return (SUCCESS);
}

int	fork_pipes (int n, t_data *data)
{
	int i;
	int in;
	int	out;
	int	fd[2];

	i = 0;
	in = data->cmds[i]->in;
	out = data->cmds[i]->out;
	while (i < n - 1)
	{
		pipe(fd);
		if (out == STDOUT_FILENO)
			spawn_proc(in, fd[1], data, data->cmds[i]->cmd);
		else
			spawn_proc(in, data->cmds[i]->out, data, data->cmds[i]->cmd);
		close(fd[1]);
		if (data->cmds[i + 1]->in == STDIN_FILENO)
			in = fd[0];
		else
			in = data->cmds[i + 1]->in;
		i++;
	}
	spawn_proc(in, data->cmds[i]->out, data, data->cmds[i]->cmd);
	close(fd[0]);
	return (SUCCESS);
}
