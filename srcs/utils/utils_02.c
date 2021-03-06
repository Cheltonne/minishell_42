/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:53:10 by chajax            #+#    #+#             */
/*   Updated: 2022/05/22 21:49:17 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_envlstsize(t_envlist *lst)
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

t_envlist	*ft_envlstnew(char *name, char *value)
{
	t_envlist	*elem;

	elem = malloc(sizeof(t_envlist));
	if (!elem)
		return (NULL);
	elem->name = name;
	elem->value = value;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_tklist	*ft_tklstnew(t_type type, char *value)
{
	t_tklist	*elem;

	elem = malloc(sizeof(t_tklist));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->value = value;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_tklist	*ft_tklstlast(t_tklist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_tklstadd_back(t_tklist **alst, t_tklist *new)
{
	t_tklist	*last;

	if (!*alst)
	{
		*alst = new;
		return (SUCCESS);
	}
	last = ft_tklstlast(*alst);
	last->next = new;
	new->prev = last;
	return (SUCCESS);
}
