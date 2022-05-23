/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:00:53 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 15:31:17 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	clean_all(char **paths, char **cmdarg, char *final)
{
	ft_chartable_free(paths);
	ft_chartable_free(cmdarg);
	free(final);
	return (0);
}

int	ft_table_count(void **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	return (i);
}

t_envlist	*ft_envlstlast(t_envlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_envlstadd_back(t_envlist **alst, t_envlist *new)
{
	t_envlist	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = ft_envlstlast(*alst);
	last->next = new;
	new->prev = last;
}

int	ft_tklstsize(t_tklist *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
