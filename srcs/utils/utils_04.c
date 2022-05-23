/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_04.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:43:40 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 13:41:26 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_wrapper(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_nb + 1)
	{
		waitpid(data->cmds[i]->id, &g_exit, 0);
		i++;
	}
}

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
			tmp = (*lst)->next;
			ft_tklstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}

void	free_everything(t_data *data)
{
	free(data->line);
	ft_tklstclear(&data->token_list, &free);
	free(data->cmds);
	unlink(".here_doc");
}

int	ad(int *value)
{
	(*value) += 1;
	return (SUCCESS);
}
