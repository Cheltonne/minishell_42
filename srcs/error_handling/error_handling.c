/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:11:00 by chajax            #+#    #+#             */
/*   Updated: 2022/05/19 14:10:14 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit(EXIT_FAILURE);
}
