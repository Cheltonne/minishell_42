/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:55:18 by phaslan           #+#    #+#             */
/*   Updated: 2022/04/20 13:46:57 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sp_char_nb(t_tklist *tokens, t_type type)
{
	int	ret;

	ret = 0;
	while (tokens->next != NULL)
	{
		if (tokens->type == type)
			ret += ft_strlen(tokens->value);
		tokens = tokens->next;
	}
	if (tokens->type == type)
			ret += ft_strlen(tokens->value);
	return (ret);
}

void	manage_squote(t_tklist **list)
{
	if ((*list)->next->type != END)
		*list = (*list)->next;
	while ((*list)->type != END && (*list)->type != S_QUOTE)
	{
			(*list)->type = LITTERAL;
			*list = (*list)->next;
	}
	return ;
}

void	manage_dquote(t_tklist **list)
{
	if ((*list)->next->type != END)
		*list = (*list)->next;
	while ((*list)->type != END && (*list)->type != D_QUOTE)
	{
		if ((*list)->type != DOLLAR)
			(*list)->type = LITTERAL;
		else if ((*list)->type == DOLLAR && (*list)->next->type != LITTERAL)
			(*list)->type = LITTERAL;
		*list = (*list)->next;
	}
	return ;
}

t_tklist	*second_scan(t_data *data)
{
	t_tklist	*head;

	head = data->token_list;
	while (data->token_list->type != END)
	{
		if (data->token_list->type == S_QUOTE)
			manage_squote(&data->token_list);
		if (data->token_list->type == D_QUOTE)
			manage_dquote(&data->token_list);
		if (data->token_list->type != END)
			data->token_list = data->token_list->next;
	}
	if (sp_char_nb(head, S_QUOTE) % 2 != 0 || sp_char_nb(head, D_QUOTE)
		% 2 != 0)
		return (NULL);
	data->token_list = head;
	return (head);
}
