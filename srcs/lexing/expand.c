/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:27:02 by chajax            #+#    #+#             */
/*   Updated: 2022/05/24 17:10:27 by chajax           ###   ########.fr       */
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

char	*true_name(char *name)
{
	int		i;
	char	*true_name;

	true_name = (char *)malloc(sizeof(char) + (ft_strlen(name)));
	i = 0;
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
		{
			true_name[i] = '\0';
			return (true_name);
		}
		true_name[i] = name[i];
		i++;
	}
	true_name[i] = '\0';
	return (true_name);
}

void	expanding(t_data *data, t_tklist *tk)
{
	char	*name;
	int		x;

	x = 0;
	name = NULL;
	if (!ft_strcmp(tk->next->value, "?"))
	{
		free(tk->next->value);
		tk->next->value = ft_itoa(g_exit);
	}
	else
	{
		printf("la valeur suivante est %s\n", tk->next->value);
		x = egal_expand(tk->next->value);
		name = true_name(tk->next->value);
		printf("le true name est %s\n", name);
		printf("le nombre de = est %d\n", x);
		free(tk->next->value);
		tk->next->value = get_venv(data->env, name);
		printf("la nouvelle valeur du $ est %s\n", tk->next->value);
		if (tk->next->value == NULL)
			tk->next->value = ft_strdup("");
		else if (x)
			tk->next->value = ft_strjoin(tk->next->value, "=", 1);
		free(name);
	}
}

void	expand(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		// printf("je suis la %s dans expand\n", tk->value);
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
