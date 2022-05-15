/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paslan <paslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:27:02 by chajax            #+#    #+#             */
/*   Updated: 2022/05/11 17:40:36 by paslan           ###   ########.fr       */
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
//	tk = tk->next;
//	del_tknode(tk->prev);
}

void	expand(t_data *data)
{
	t_tklist *tk;

	tk = data->token_list;
	while (tk->type != END)
	{
		if (tk->type == DOLLAR)
		{
			if (tk->next->type == LITTERAL)
			{
			expanding(data, tk);
			//	tk->next->value = get_venv(data->env, tk->next->value);
			//	if (tk->next->value == NULL)
			//		tk->next->value = ft_strdup("");
			tk = tk->next;
			del_tknode(tk->prev);
				// ici c pas bon, je dois check toute la string jusqu'a 
				// tomber sur un char invalide
				// je check si la string up until non-valid est dans mon env
				// si oui, je vais dump ca

				// il me faut un cas special pour l'expand du g_exit
				// je vais check si jamais le litt suivant c un ?
				// si oui je vais aller itoa la valeur de g_exit into le maillon
				// je rends l'apparail au checkeur d'expand
				// autant faire tout ca dans une fonction, le cas special avec ?
				// je vais la nommer expansions_expanded
/*				if (tk->prev)
				{
					if (tk->prev->type == LITTERAL)
					{
						tk->next->value = ft_strjoin(tk->prev->value, tk->next->value);
						del_tknode(tk->prev);
						tk = tk->next;
					}
				} */
			}
		}
		//if (tk->type != END)
		//	printf("%s test %d type\n", tk->value, tk->type);
		if (tk->type != END)
			tk = tk->next;
	}
}
