/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:38 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/24 17:12:25 by chajax           ###   ########.fr       */
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
			name = ft_strjoin(copy->name, "=", 0);
			ft_putstr_fd(name, data->cmds[0]->out);
			ft_putstr_fd(copy->value, data->cmds[0]->out);
			ft_putstr_fd("\n", data->cmds[0]->out);
			copy = copy->next;
			free(name);
		}
	}
	return (SUCCESS);
}
