/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:05:50 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 14:09:48 by phaslan          ###   ########.fr       */
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

int	echo_cmd(char **args)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (check_opt(args[1]) && !args[2])
		return (0);
	while (check_opt(args[++i]))
		option++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}
