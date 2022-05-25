/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:06:15 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 09:42:36 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_formatting(t_data *data)
{
	t_tklist	*head;

	head = data->token_list;
	data->token_list = expand(data);
	data->token_list = join_litterals(data);
	data->token_list = suppr_quotes(data);
	data->token_list = join_litt(data);
	data->token_list = syntax_error(data);
	if (data->token_list == NULL)
	{
		data->token_list = head;
		ft_tklstclear(&data->token_list, &free);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
