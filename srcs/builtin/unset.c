/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:31:21 by phaslan           #+#    #+#             */
/*   Updated: 2022/04/19 15:49:48 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// d'ailleurs remplace celui dans quote.c par ca

int	not_valid_env_arg(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]))
		return (1);
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
		{
			printf("je crash a ce %c", arg[i]);
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

// j'arrive pas a en unset plusieurs d'un coup ??
// pk j'ai pas reussi a unset 2 trucs d'un coup
// j'arrive a unset plusieurs trucs
// j'arrive pas a unset un truc en particulier, en rapport avec la position dans la liste chaine, mais quoi
// dans le cas ou j'ai salut331 et salut3 se vais unset salut3

int	unset_cmd(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		while (argv[i] && not_valid_env_arg(argv[i]))
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
	// free array 2d de env
	// redup l'env en 2d
	return (0);
}