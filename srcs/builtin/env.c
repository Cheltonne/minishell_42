/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:38 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 17:05:18 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_cmd(t_data *data)
{	
	t_envlist	*copy;
	char		*name;

	copy = data->env;
	while (copy)
	{
		if (!copy->value)
			break ;
		while (copy->name != NULL)
		{
			name = ft_strjoin(copy->name, "=");
			ft_putstr_fd(name, 1);
			ft_putstr_fd(copy->value, 1);
			ft_putstr_fd("\n", 1);
			copy = copy->next;
		}
	}
	free(name);
	return (SUCCESS);
}
