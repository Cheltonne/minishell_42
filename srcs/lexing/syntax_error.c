/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:04:18 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/25 16:29:16 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*pip_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	return (NULL);
}

t_tklist	*pipe_scan(t_data *data)
{
	int			x;
	t_tklist	*tk;

	tk = data->token_list;
	x = 0;
	while (tk->type != END)
	{
		if (tk->type == LITTERAL)
			x = 1;
		if (tk->type == PIPE && x == 0)
			return (pip_error("bash: syntax error near unexpected token `|'\n"));
		else if (tk->type == PIPE && x == 1)
		{
			x = 0;
			while (tk->next->type != END && tk->next->type == WHITESPACE)
				tk = tk->next;
			if (tk->type == END)
				return (NULL);
		}
		else
			tk = tk->next;
	}
	return (data->token_list);
}

t_tklist	*syntax_error(t_data *data)
{
	data->token_list = pipe_scan(data);
	data->token_list = redir_scan(data);
	return (data->token_list);
}
