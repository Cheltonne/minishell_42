/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:27:02 by chajax            #+#    #+#             */
/*   Updated: 2022/05/19 14:10:52 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoinzero(char const *s2, char const *s1)
{
	int		i;
	int		o;
	int		total_len;
	char	*new;

	i = 0;
	o = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = malloc(sizeof(char) * total_len);
	if (!new)
		return (NULL);
	while (s1[i])
		new[o++] = s1[i++];
	i = 0;
	while (s2[i])
		new[o++] = s2[i++];
	new[o] = '\0';
	return (new);
}

void	expanding(t_data *data, t_tklist *tk)
{
	if (!ft_strcmp(tk->next->value, "?"))
		tk->next->value = ft_itoa(g_exit);
	else
	{
		tk->next->value = get_venv(data->env, tk->next->value);
		if (tk->next->value == NULL)
			tk->next->value = ft_strdup("");
	}
}

void	expand(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		if (tk->type == DOLLAR)
		{
			if (tk->next->type == LITTERAL)
			{
				expanding(data, tk);
				tk = tk->next;
				del_tknode(tk->prev);
			}
		}
		if (tk->type != END)
			tk = tk->next;
	}
}
