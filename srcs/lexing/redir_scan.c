/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:40:45 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/25 13:56:08 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int g_exit;

t_tklist	*arrow_ncheck(t_tklist *tk)
{
	while (tk->type != END)
	{
		if (tk->type == R_REDIR || tk->type == L_REDIR)
		{
			if (ft_strlen(tk->value) > 2)
			{
				g_exit = 2;
				if (tk->type == R_REDIR)
					ft_putstr_fd("bash:syntax error near token '>>'\n", 2);
				if (tk->type == L_REDIR)
					ft_putstr_fd("bash:syntax error near token '<<'\n", 2);
				return (NULL);
			}
		}
		tk = tk->next;
	}
	while (tk->prev != NULL)
		tk = tk->prev;
	return (tk);
}

int	parse_error(int i)
{
	if (i == 0)
		ft_putstr_fd("bash:parse error near token '\\n'\n", 2);
	if (i == 1)
		ft_putstr_fd("bash:parse error near token '>'\n", 2);
	if (i == 2)
		ft_putstr_fd("bash:parse error near token '<'\n", 2);
	return (2);
}

int	manage_arrow(t_tklist **tk)
{
	*tk = (*tk)->next;
	if ((*tk)->type != WHITESPACE)
		return (0);
	return (1);
}

int	arrow_analyse(t_tklist *data)
{
	t_tklist	*tk;

	tk = data;
	if (tk->next->type == END)
		return (parse_error(0));
	else if (tk->type == R_REDIR)
	{
		while (tk->prev != NULL)
			if (!manage_arrow(&tk))
				break ;
		if (tk->type != LITTERAL)
			return (parse_error(1));
	}
	else if (tk->type == L_REDIR)
	{
		while (tk->next->type != END)
			if (!manage_arrow(&tk))
				break ;
		if (tk->type != LITTERAL)
			return (parse_error(2));
	}
	return (0);
}

t_tklist	*redir_scan(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	if (tk == NULL)
		return (NULL);
	tk = arrow_ncheck(tk);
	while (tk->type != END)
	{
		if (tk->type == R_REDIR || tk->type == L_REDIR)
		{
			g_exit = arrow_analyse(tk);
			if (g_exit == 2)
				return (NULL);
			if (ft_strlen(tk->value) == 2)
			{
				if (tk->type == R_REDIR)
					tk->type = APPEND;
				else if (tk->type == L_REDIR)
					tk->type = HERE_DOC;
			}
		}
		tk = tk->next;
	}
	return (data->token_list);
}
