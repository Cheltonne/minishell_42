/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:05:03 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/25 16:16:48 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	try_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (FAILURE);
	ft_putstr_fd(path, data->cmds[0]->out);
	ft_putstr_fd("\n", data->cmds[0]->out);
	free(path);
	return (SUCCESS);
}
