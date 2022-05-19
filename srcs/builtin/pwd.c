/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:05:03 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 17:05:56 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	try_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
