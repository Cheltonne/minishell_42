/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:31:21 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 16:33:25 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	not_valid_env_arg(char *arg, int x)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]))
		return (1);
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
		{
			if (x == 3)
				ft_putstr_fd("not a correct env identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

t_envlist	*unset_env(t_envlist *env, char *arg)
{
	while (env->next)
	{
		if (!ft_strcmp(env->name, arg))
		{
			env = env->next;
			del_node(env->prev);
		}
		if (env->next != NULL)
			env = env->next;
	}
	while (env->prev != NULL)
		env = env->prev;
	return (env);
}

int	unset_cmd(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		while (argv[i] && not_valid_env_arg(argv[i], 0))
			i++;
		if (!argv[i])
			break ;
		if (data->env)
		{
			data->env = unset_env(data->env, argv[i]);
		}
		i++;
	}
	data->env_arr = dupenv(data->env);
	return (0);
}
