/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_fcts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:45:09 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 15:12:17 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redir_anal(t_tklist **head, t_cmd **ret, int *i)
{
	if ((*head)->type == L_REDIR)
		return (left_redirection(ret, &head));
	else if ((*head)->type == R_REDIR)
		return (right_redirection(ret, &head));
	else if ((*head)->type == APPEND)
	{
		if (append(ret, &head))
			;
		else
			(*ret)->cmd[(*i++)] = NULL;
	}
	else if ((*head)->type == HERE_DOC)
		return (here_doc(ret, &head));
	return (3);
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

int	here_doc(t_cmd **ret, t_tklist ***head)
{
	int		buf_fd;

	while ((**head)->type != END && (**head)->type != LITTERAL)
		**head = (**head)->next;
	if ((**head)->type != END)
	{
		buf_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (buf_fd < 0)
			exit(EXIT_FAILURE);
		query_user((**head)->value, &buf_fd);
		close(buf_fd);
		(*ret)->in = open(".here_doc", O_RDONLY);
		if ((*ret)->out < 0)
		{
			unlink(".here_doc");
			ft_putstr_fd("Couldn't open here_document buffer file.\n", 2);
			return (FAILURE);
		}
		**head = (**head)->next;
		if (here_doc_empty((*ret)->in) == TRUE)
			return (FAILURE);
	}
	return (SUCCESS);
}
