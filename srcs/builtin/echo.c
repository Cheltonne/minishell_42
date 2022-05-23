/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:05:50 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/22 20:16:11 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_opt(char *args)
{
	int	i;

	i = 2;
	if (args && (args[0] == '-' && args[1] == 'n'))
	{
		while (args[i] == 'n')
			i++;
		if (args[i] == '\0')
			return (1);
	}
	return (0);
}

int	echo_cmd(t_cmd *command, t_data *data)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!command->cmd[1])
	{
		ft_putstr_fd("\n", data->cmds[0]->out);
		return (0);
	}
	if (check_opt(command->cmd[1]) && !command->cmd[2])
		return (0);
	while (check_opt(command->cmd[++i]))
		option++;
	while (command->cmd[i])
	{
		ft_putstr_fd(command->cmd[i], data->cmds[0]->out);
		i++;
		if (command->cmd[i])
			ft_putstr_fd(" ", data->cmds[0]->out);
	}
	if (!option)
		ft_putstr_fd("\n", data->cmds[0]->out);
	return (0);
}
