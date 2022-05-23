/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:40:45 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/22 22:05:48 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	arrow_analyse(t_tklist *data)
{
	t_tklist	*tk;

	tk = data;
	if (tk->next->type == END)
	{
		ft_putstr_fd("bash:parse error near token '\\n'\n", 2);
		return (2);
	}
	else if (tk->type == R_REDIR)
	{
		while (tk->prev != NULL)
		{
			tk = tk->next;
			if (tk->type != WHITESPACE)
				break ;
		}
		if (tk->type != LITTERAL)
		{
			ft_putstr_fd("bash:parse error near token '>\n'", 2);
			return (2);
		}
	}
	else if (tk->type == L_REDIR)
	{
		while (tk->next->type != END)
		{
			tk = tk->next;
			if (tk->type != WHITESPACE)
				break ;
		}
		if (tk->type != LITTERAL)
		{
			ft_putstr_fd("bash:parse error near token <\n", 2);
			return (2);
		}
	}
	return (0);
}

t_tklist	*redir_scan(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	tk = arrow_ncheck(tk);
	if (tk == NULL)
		return (NULL);
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
	while (tk->prev != NULL)
		tk = tk->prev;
	return (tk);
}
