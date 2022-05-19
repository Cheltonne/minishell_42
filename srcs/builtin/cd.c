/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:06:33 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/19 14:10:05 by phaslan          ###   ########.fr       */
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

void	update_cd(t_data *data)
{
	char	*name[3];

	name[0] = ft_strdup("export");
	name[1] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	name[2] = ft_strdup("\0");
	export_cmd(data, name);
}

int	cd_cmd(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("cd : too many args\n", 2);
		return (0);
	}
	if (!args[1] || args[1][0] == '~')
		return (go_home());
	if (check_path(args[1]))
		return (0);
	update_cd(data);
	chdir(args[1]);
	return (0);
}
