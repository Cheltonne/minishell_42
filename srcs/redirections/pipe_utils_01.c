/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:47:47 by chajax            #+#    #+#             */
/*   Updated: 2022/05/19 22:42:25 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fork_wrapper(pid_t *child)
{
	*child = fork();
	if (*child < 0)
		(perror("Fork"));
}

void	exec_builtin_pipe(t_data *data, char **cmd)
{
	fork_wrapper(&data->id);
	if (data->id == CHILD)
	{
		g_exit = exec_builtin(data, cmd);
	//	free
		exit(g_exit);
	}
}

int	spawn_proc(int in, int out, t_data *data, char **cmd)
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
		if (is_builtin(cmd))
		{
			g_exit = exec_builtin(data, cmd);
			exit(g_exit);
		}
		execute(cmd, data->env_arr);
    }
	return (SUCCESS);
}

int	fork_pipes(int n, t_data *data)
{
	int	i;
	int	io[2];
	int	fd[2];

	i = 0;
	io[0] = data->cmds[i]->in;
	io[1] = data->cmds[i]->out;
	while (i < n - 1)
	{
		pipe(fd);
		if (io[1] == STDOUT_FILENO)
			spawn_proc(io[0], fd[1], data, data->cmds[i]->cmd);
		else
			spawn_proc(io[0], data->cmds[i]->out, data, data->cmds[i]->cmd);
		close(fd[1]);
		if (data->cmds[i + 1]->in == STDIN_FILENO)
		{
			io[0] = fd[0];
			close(fd[0]);
		}
		else
			io[0] = data->cmds[i + 1]->in;
		i++;
	}
	spawn_proc(io[0], data->cmds[i]->out, data, data->cmds[i]->cmd);
	close(fd[0]);
	return (SUCCESS);
}
