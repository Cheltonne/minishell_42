/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:47:47 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 22:49:05 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fork_wrapper(pid_t *child)
{
	*child = fork();
	if (*child < 0)
		(perror("Fork"));
}

int	dup_wrapper(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		exit (g_exit);
	close (oldfd);
	return (SUCCESS);
}

int	spawn_proc(int in, int out, t_data *data, t_cmd *command)
{
	fork_wrapper(&command->id);
	if (command->id == CHILD)
	{
		if (in != STDIN_FILENO)
		{
			dup_wrapper(in, STDIN_FILENO);
			close(data->fd[READ]);
		}
		else
			close(data->fd[READ]);
		if (out != STDOUT_FILENO)
			dup_wrapper(out, STDOUT_FILENO);
		else
			close(data->fd[WRITE]);
		if (is_builtin(command->cmd))
		{
			g_exit = exec_builtin(data, command);
			exit(g_exit);
		}
		execute(data, command->cmd, data->env_arr);
	}
	return (SUCCESS);
}

int	fork_pipes(int n, t_data *data)
{
	int	i;
	int	io[2];

	i = 0;
	io[0] = data->cmds[i]->in;
	io[1] = data->cmds[i]->out;
	while (i < n - 1)
	{
		pipe(data->fd);
		if (io[1] == STDOUT_FILENO)
			spawn_proc(io[0], data->fd[1], data, data->cmds[i]);
		else
			spawn_proc(io[0], data->cmds[i]->out, data, data->cmds[i]);
		close(data->fd[1]);
		if (io[0] != STDIN_FILENO)
			close(io[0]);
		(void)(((data->cmds[i + 1]->in == STDIN_FILENO) && (io[0] = data->fd[0]))\
		|| (io[0] = data->cmds[i + 1]->in));
		i++;
	}
	spawn_proc(io[0], data->cmds[i]->out, data, data->cmds[i]);
	close(io[0]);
	close(data->fd[0]);
	return (SUCCESS);
}
