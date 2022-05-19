/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:06:33 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 21:40:23 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	n;
	int	x;

	i = 0;
	n = ft_strlen(s1);
	x = ft_strlen(s2);
	if (x != n)
		return (1);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_builtin(char **cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd[0], "env"))
		return (1);
	if (!ft_strcmp(cmd[0], "export"))
		return (1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_data *data, char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd_cmd(data, cmd));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (try_pwd(data));
	if (!ft_strcmp(cmd[0], "echo"))
		return (echo_cmd(cmd, data));
	if (!ft_strcmp(cmd[0], "unset"))
		return (unset_cmd(data, cmd));
	if (!ft_strcmp(cmd[0], "env"))
		return (env_cmd(data));
	if (!ft_strcmp(cmd[0], "export"))
		return (export_cmd(data, cmd));
	if (!ft_strcmp(cmd[0], "exit"))
		return (exit_cmd(data, cmd));
	return (1);
}
