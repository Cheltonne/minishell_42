/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:55:24 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 17:18:43 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_export(t_data *data)
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
			ft_putstr_fd("export ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(copy->value, 2);
			ft_putstr_fd("\n", 2);
			copy = copy->next;
		}
	}
	free(name);
}

int	env_rp_value(char *name, t_envlist *env, char *value)
{
	t_envlist	*current;

	current = env;
	while (current->name != NULL)
	{
		if (!ft_strcmp(current->name, name))
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

char	*get_venv(t_envlist *env, char *name)
{
	t_envlist	*current;
	char		*nameu;

	current = env;
	while (current->name != NULL)
	{
		if (!ft_strcmp(current->name, name))
		{
			if (!current->value)
				return ("");
			nameu = ft_strdup(current->value);
			return (nameu);
		}
		current = current->next;
	}
	return (NULL);
}

void	node_add(t_envlist *lst, char *name, char *value, t_data *data)
{
	if (get_venv(data->env, name))
		env_rp_value(name, data->env, value);
	else
	{
		lst = ft_envlstlast(lst);
		lst->name = ft_strdup(name);
		lst->value = ft_strdup(value);
		ft_envlstadd_back(&data->env, ft_envlstnew(NULL, NULL));
	}
}

int	export_cmd(t_data *data, char **cmd)
{
	char		*name;
	char		*value;
	int			i;
	t_envlist	*lst;

	name = NULL;
	value = NULL;
	i = 1;
	lst = ft_envlstlast(data->env);
	if (!cmd[1])
		env_export(data);
	while (cmd[i])
	{
		name = set_name(cmd[i]);
		if (!name)
			return (1);
		if (not_valid_env_arg(name, 3))
			return (1);
		value = set_value(cmd[i]);
		if (!value)
			value = ft_strdup("");
		node_add(lst, name, value, data);
		i++;
	}
	return (1);
}
