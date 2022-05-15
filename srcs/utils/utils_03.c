/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:26:27 by chajax            #+#    #+#             */
/*   Updated: 2022/04/20 16:21:51 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_node(t_envlist *node)
{
	if (node->prev == NULL)
	{
		node->next->prev = NULL;
		free(node);
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node->name);
		free(node->value);
		free(node);
	}
}

void	del_tknode(t_tklist *node)
{
	if (node->prev == NULL)
	{
		node->next->prev = NULL;
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

/* void	manage_fquote(t_tklist *list)
{
	if ((list)->next->type != END)
		list = (list)->next;
	while ((list)->next->type != END && (list)->next->type != D_QUOTE)
	{
		list = list->next;
		printf(" =====\n %s\n et %s\n =====\n ca devient\n", (list)->prev->value, (list)->value);
		list->value = ft_strjoin((list)->prev->value, (list)->value);
		printf("%s", (list)->value);
		del_tknode((list)->prev);
	}
	return ;
} */

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
					tk->next->value = ft_strjoin(tk->value, tk->next->value);
					tk = tk->next;
					del_tknode(tk->prev);
					// printf("la ma string avance comme ca %s\n", tk->value);
				}
				else
					break ;
			}
			tk = tk->next;
		}
		if (tk->type != END)
			tk = tk->next;
	}
	while (tk->prev)
		tk = tk->prev;
	return (tk);
}

// ici je suppr toutes les quotes que je trouve
// j'aimerais bien join les litterals sans white space entre deux mais bon la frero c oh merde
// autant faire une nouvelle fonction
t_tklist *suppr_quotes(t_data *data)
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
		else if  (tk->type != END)
		{
			// printf("%s\n", tk->value);
			tk = tk->next;
		}
	}
	// printf("\n");
	while (tk->prev)
		tk = tk->prev;
	return (tk);
}

t_tklist *join_litt(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		if (tk->type == LITTERAL && tk->next->type == LITTERAL)
		{
			//printf("on a les tokens %s et %s\n", tk->value, tk->next->value);
			tk->value = ft_strjoin(tk->value, tk->next->value);
			// printf("join litt :%s\n", tk->value);
			del_tknode(tk->next);
		}
		else
			tk = tk->next;
	}
	// printf("\n");
	while (tk->prev)
		tk = tk->prev;
	return (tk);
}

// ok ma variable d'env est corrompu par ma loop join litterals
// pourtant elle essaie juste de concatener des strings dans une variable aaaaah je renvoie un pointeur sur la variable, et pas une string egale a la