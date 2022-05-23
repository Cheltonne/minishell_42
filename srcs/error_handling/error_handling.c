/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:11:00 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 21:22:54 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	verify_main_args(int argc, char **argv, char **envp)
{
	if (argv && argc != 1)
		exit_error("minishell does not accept any arguments 😰😱😨😰😥😓\n");
	(void)envp;
}

void	exit_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}
