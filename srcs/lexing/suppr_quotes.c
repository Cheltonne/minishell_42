/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:43:52 by phaslan           #+#    #+#             */
/*   Updated: 2022/04/19 18:53:35 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tklist *suppr_quotes(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk)
	{
		while (tk->type != D_QUOTE || tk->type != S_QUOTE)
			tk = tk->next;
		if (tk->type == D_QUOTE || tk->type == S_QUOTE)
		{
			tk = tk->prev;
			del_tknode(tk->next);
			if (tk->type == LITTERAL && tk->type->next == LITTERAL)
			{
				tk->value = ft_strjoin(tk->value, tk->next->value);
				del_tknode(tk->next);
			}
		}
		tk = tk->next;
	}
}