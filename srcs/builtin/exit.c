/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:38 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/23 21:40:00 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define LLMAX_D10 922337203685477580

void	free_env(t_envlist *lst)
{
	t_envlist	*tmp;

	if (lst)
	{
		while (lst->value != NULL)
		{
			tmp = lst->next;
			del_node(lst);
			lst = tmp;
		}
		free(lst->name);
		free(lst->value);
		free(lst);
	}
}

void	free_tokens(t_tklist *lst)
{
	t_tklist	*tmp;

	if (lst)
	{
		while (lst->type != END)
		{
			tmp = lst->next;
			del_tknode(lst);
			lst = tmp;
		}
	}
}

int	ft_atoll_err(char *str, long long int *nbr)
{
	int						neg;
	unsigned long long int	abs;

	if (!*str)
		return (1);
	neg = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	abs = 0;
	while (*str == '0')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (abs >= LLMAX_D10 && (abs > LLMAX_D10 || *str > ('7' + neg)))
			return (1);
		abs *= 10;
		abs += *str - '0';
		str++;
	}
	if (*str)
		return (1);
	*nbr = abs;
	if (neg)
		*nbr = -abs;
	return (0);
}

int	ft_strdigit(char *str)
{
	long long int	status;

	status = -1;
	if (ft_atoll_err(str, &status))
	{
		ft_putstr_fd("exit:error", 2);
		return (2);
	}
	status &= 255ULL;
	return ((int)status);
}

int	exit_cmd(t_data *data, t_cmd *command)
{
	if (command->cmd[1] && command->cmd[2])
	{
		ft_putstr_fd("exit:too many arguments", 2);
		return (1);
	}
	else
	{
		clear_history();
		//free_env(data->env);
		//free_tokens(data->token_list);
		if (data->pipe_nb == 0)
			ft_putstr_fd("exit\n", 2);
		if (command->cmd[1] != NULL)
			g_exit = ft_strdigit(command->cmd[1]);
		//ft_chartable_free(data->env_arr);
		free_everything(data);
		exit(g_exit);
	}
}
