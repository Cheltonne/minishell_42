/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:10:25 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 19:24:14 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_tklstdelone(t_tklist *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->value);
	free(lst);
}

void	ft_tklstclear(t_tklist **lst, void (*del)(void*))
{
	t_tklist	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->prev;
			ft_tklstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}

void	free_dual_token_arr(t_token **tokens, int tokens_len)
{
	int	i;

	i = 0;
	while (i < tokens_len)
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_cmds(t_data *data)
{
	int	i;
	int o;

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
	free_cmds(data);
	unlink(".here_doc");
}

void	free_everything(t_data *data)
{
	temp_free(data);
	free_env(data->env);
	ft_chartable_free(data->env_arr);
	free(data);
}
