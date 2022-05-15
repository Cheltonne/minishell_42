/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:37:21 by phaslan           #+#    #+#             */
/*   Updated: 2022/03/26 07:01:39 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

char	error_char(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

void	*null_error(char *message)
{
	ft_error(message);
	return (0);
}
