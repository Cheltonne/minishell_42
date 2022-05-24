/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:22:49 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 01:14:57 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_node(t_envlist *node)
{
	if (node->prev == NULL)
	{
		node->next->prev = NULL;
		free(node->string);
		free(node->name);
		free(node->value);
		free(node);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node->name);
		free(node->string);
		free(node->value);
		free(node);
	}
}

void	del_tknode(t_tklist *node)
{
	if (node->prev == NULL)
	{
		node->next->prev = NULL;
		free(node->value);
		free(node);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node->value);
		free(node);
	}
}

t_tklist	*join_litterals(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		if (tk->type == D_QUOTE)
		{
			tk = tk->next;
			while (tk->type != END && tk->next->type != D_QUOTE)
			{
				if (tk->type != D_QUOTE)
				{
					tk->next->value = ft_strjoin(tk->value, tk->next->value, 2);
					tk = tk->next;
					del_tknode(tk->prev);
				}
				else
					break ;
			}
			tk = tk->next;
		}
		if (tk->type != END)
			tk = tk->next;
	}
	return (data->token_list);
}

t_tklist	*suppr_quotes(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		if (tk->type == D_QUOTE || tk->type == S_QUOTE)
		{
			tk = tk->next;
			del_tknode(tk->prev);
		}
		else if (tk->type != END)
		{
			tk = tk->next;
		}
	}
	while (tk->prev)
		tk = tk->prev;
	return (tk);
}

t_tklist	*join_litt(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		if (tk->type == LITTERAL && tk->next->type == LITTERAL)
		{
			tk->value = ft_strjoin(tk->value, tk->next->value, 1);
			del_tknode(tk->next);
		}
		else
			tk = tk->next;
	}
	while (tk->prev)
		tk = tk->prev;
	return (tk);
}
