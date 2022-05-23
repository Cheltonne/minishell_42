/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:06:33 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/23 21:49:25 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_path(char *path)
{
	void		*dir;
	struct stat	st;

	ft_bzero(&st, sizeof(struct stat));
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	closedir(dir);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" ", 2);
	if (stat(path, &st) == -1)
		ft_putstr_fd("no such file or directory\n", 2);
	else if (S_ISDIR(st.st_mode))
		ft_putstr_fd("permission denied\n", 2);
	else
		ft_putstr_fd("not a directory\n", 2);
	return (1);
}

int	go_home(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (0);
	}
	chdir(path);
	return (0);
}

void	update_cd(t_data *data, t_cmd *command, char *oldpwd)
{
	free(command->cmd[0]);
	free(command->cmd[1]);
	free(command->cmd[2]);
	command->cmd[0] = ft_strdup("export");
	command->cmd[1] = ft_strjoin("OLDPWD=", oldpwd, 0);
	command->cmd[2] = ft_strdup("\0");
	export_cmd(data, command);
}

int	cd_cmd(t_data *data, t_cmd *command)
{
	int		i;
	char	*cwd_buf;
	char	*oldpwd_buf;

	i = 0;
	while (command->cmd[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("cd : too many args\n", 2);
		return (0);
	}
	if (!command->cmd[1] || command->cmd[1][0] == '~')
		return (go_home());
	if (check_path(command->cmd[1]))
		return (0);
	cwd_buf = getcwd(NULL, 0);
	oldpwd_buf = ft_strdup(cwd_buf);
	free(cwd_buf);
	chdir(command->cmd[1]);
	update_cd(data, command, oldpwd_buf);
	free(oldpwd_buf);
	return (0);
}
