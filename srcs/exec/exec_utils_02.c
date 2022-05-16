/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:40:59 by chajax            #+#    #+#             */
/*   Updated: 2022/05/16 16:48:36 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_builder_norm(t_tklist **head, t_cmd **ret, int *i)
{
	while ((*head)->type != END && (*head)->type != PIPE)
	{
		while ((*head)->type == LITTERAL || (*head)->type == WHITESPACE || 
				(*head)->type == L_REDIR || (*head)->type == R_REDIR)
		{
			if ((*head)->type == LITTERAL)
				(*ret)->cmd[(*i++)] = ft_strdup((*head)->value);
			redir_anal(head, ret, i);
			if ((*head)->type != END)
				(*head) = (*head)->next;
		}
		if (is_end(head) == TRUE)
			break ;
	}
}

int	is_end(t_tklist **head)
{
	if ((*head)->type != END)
	{
		(*head) = (*head)->next;
		return (FALSE);
	}
	return (TRUE);
}

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
