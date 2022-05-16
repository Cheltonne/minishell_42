/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_fcts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:45:09 by chajax            #+#    #+#             */
/*   Updated: 2022/05/16 19:10:34 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_anal(t_tklist **head, t_cmd **ret, int *i)
{
	if ((*head)->type == L_REDIR)
	{
		if (left_redirection(ret, &head))
			;
		else
			(*ret)->cmd[(*i++)] = NULL;
	}
	if ((*head)->type == R_REDIR)
	{
		if (right_redirection(ret, &head))
			;
		else
			(*ret)->cmd[(*i++)] = NULL;
	}
	if ((*head)->type == APPEND)
	{
		if (append(ret, &head))
			;
		else
			(*ret)->cmd[(*i++)] = NULL;
	}
}

int	left_redirection(t_cmd **ret, t_tklist ***head)
{
	while ((**head)->type != END && (**head)->type != LITTERAL)
		**head = (**head)->next;
	if ((**head)->type != END)
	{
		(*ret)->in = open((**head)->value, O_RDONLY);
		if ((*ret)->in < 0)
		{
			ft_putstr_fd((**head)->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (FAILURE);
		}
		**head = (**head)->next;
	}
	return (SUCCESS);
}

int	right_redirection(t_cmd **ret, t_tklist ***head)
{
	while ((**head)->type != END && (**head)->type != LITTERAL)
		**head = (**head)->next;
	if ((**head)->type != END)
	{
		(*ret)->out = open((**head)->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*ret)->out < 0)
		{
			ft_putstr_fd((**head)->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (FAILURE);
		}
		**head = (**head)->next;
	}
	return (SUCCESS);
}

int	append(t_cmd **ret, t_tklist ***head)
{
	while ((**head)->type != END && (**head)->type != LITTERAL)
		**head = (**head)->next;
	if ((**head)->type != END)
	{
		(*ret)->out = open((**head)->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*ret)->out < 0)
		{
			ft_putstr_fd((**head)->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (FAILURE);
		}
		**head = (**head)->next;
	}
	return (SUCCESS);
}
