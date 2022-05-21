/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:47:47 by chajax            #+#    #+#             */
/*   Updated: 2022/05/21 21:39:14 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fork_wrapper(pid_t *child)
{
	*child = fork();
	if (*child < 0)
		(perror("Fork"));
}

int	spawn_proc(int in, int out, int fd[2], t_data *data, t_cmd *command)
{
	fork_wrapper(&command->id);
	if (command->id == CHILD)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
			close(fd[READ]);
		}
		else
			close(fd[READ]);
		if (out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		else
			close(fd[WRITE]);
		if (is_builtin(command->cmd))
		{
			g_exit = exec_builtin(data, command->cmd);
			exit(g_exit);
		}
		execute(command->cmd, data->env_arr);
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
			spawn_proc(io[0], fd[1], fd, data, data->cmds[i]);
		else
			spawn_proc(io[0], data->cmds[i]->out, fd, data, data->cmds[i]);
		close(fd[1]);
		if (io[0] != STDIN_FILENO)
			close(io[0]);
		if (data->cmds[i + 1]->in == STDIN_FILENO)
			io[0] = fd[0];
		else
			io[0] = data->cmds[i + 1]->in;
		i++;
	}
	spawn_proc(io[0], data->cmds[i]->out, fd, data, data->cmds[i]);
	close(io[0]);
	close(fd[0]);
	return (SUCCESS);
}
