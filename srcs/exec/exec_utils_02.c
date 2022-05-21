/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:40:59 by chajax            #+#    #+#             */
/*   Updated: 2022/05/21 22:59:46 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_builder_norm(t_tklist **head, t_cmd **ret, int *i)
{
	while ((*head)->type != END && (*head)->type != PIPE)
	{
		while ((*head)->type == LITTERAL || (*head)->type == WHITESPACE
			|| (*head)->type == L_REDIR || (*head)->type == R_REDIR
			|| (*head)->type == APPEND || (*head)->type == HERE_DOC)
		{
			if ((*head)->type == LITTERAL)
			{
				(*ret)->cmd[(*i)] = ft_strdup((*head)->value);
				(*i) += 1;
			}
			redir_anal(head, ret, i);
			if ((*head)->type != END)
				(*head) = (*head)->next;
		}
		if ((*head)->type != END)
		{
			(*head) = (*head)->next;
			break ;
		}
	}
}

int	pipe_count(t_tklist *token_list)
{
	int	ret;
	t_tklist *head;

	ret = 0;
	head = token_list;
	while (head->type != END)
	{
		if (head->type == PIPE)
			ret++;
		head = head->next;
	}
	return (ret);
}

void	exec_single_cmd(t_data *data)
{
	if (is_builtin(data->cmds[0]->cmd))
	{
		g_exit = exec_builtin(data, data->cmds[0]->cmd);
		return ;
	}
	fork_wrapper(&data->cmds[0]->id);
	if (data->cmds[0]->id == 0)
	{
		if (data->cmds[0]->in != 0 || data->cmds[0]->out != 1)
		{
			dup2(data->cmds[0]->in, STDIN_FILENO);
			dup2(data->cmds[0]->out, STDOUT_FILENO);
		}
		execute(data->cmds[0]->cmd, data->env_arr);
	}
}
