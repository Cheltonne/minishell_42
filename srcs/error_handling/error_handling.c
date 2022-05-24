/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:11:00 by chajax            #+#    #+#             */
/*   Updated: 2022/05/24 15:51:21 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	verify_main_args(int argc, char** argv)
{
	if (argv && argc != 1)
		exit_error("minishell does not accept any arguments 😰😱😨😰😥😓\n");
}

void	exit_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}

int	egal_expand(char *name)
{
	int	i;

	i = 0;
	printf("j'ai cte string dans le = check %s\n", name);
	while (name[i])
		i++;
	printf("je suis la %c\n", name[i - 1]);
	if (name[i - 1] == '=')
		return (1);
	else
		return (0);
}
