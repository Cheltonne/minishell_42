/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:10:25 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 16:15:32 by chajax           ###   ########.fr       */
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
			tmp = (*lst)->next;
			ft_tklstdelone(*lst, del);
			(*lst) = tmp;
		}
		ft_tklstdelone(*lst, del);
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
