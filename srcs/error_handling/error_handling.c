/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:11:00 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 01:19:45 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	verify_main_args(int argc, char **argv)
{
	if (argv && argc != 1)
	{
		ft_putstr_fd("minishell does not take any args\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	exit_error(char *error_msg, t_data *data)
{
	ft_putstr_fd(error_msg, 2);
	free_everything(data);
	exit(EXIT_FAILURE);
}

int	egal_expand(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	if (name[i - 1] == '=')
		return (1);
	else
		return (0);
}
