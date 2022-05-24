/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:56:07 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/24 16:37:55 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*cmd_builder(t_tklist **head)
{
	int			i;
	t_cmd		*ret;

	i = 0;
	ret = ft_calloc(1, sizeof(t_cmd));
	ret->cmd = ft_calloc(ft_tklstsize(*head), sizeof(char *));
	if (!ret)
		return (NULL);
	ret->in = 0;
	ret->out = 1;
	cmd_builder_norm(head, &ret, &i);
	ret->cmd[i] = NULL;
	return (ret);
}

char	**get_all_paths(char **enpv, int line)
{
	char	**paths;
	int		i;

	i = 0;
	while (*enpv)
	{
		if (ft_strnstr(*enpv, "PATH", 5))
		{
			while (**enpv != '/')
				*enpv += 1;
			paths = ft_split(*enpv, ':');
			if (!paths)
				return (null_error("Unable to allocate PATHS 😱"));
			return (paths);
		}
		if (++i == line)
		{
			perror("Unable to find PATH 😨");
			return (0);
		}
		enpv++;
	}
	return (NULL);
}

char	*search_path(char **paths, char *cmdarg)
{
	int		i;
	char	*final_cmd;
	char	*buff;

	i = 0;
	if (access(cmdarg, R_OK) == 0)
		return (cmdarg);
	while (paths[i])
	{
		buff = ft_strjoin(paths[i], "/", 0);
		if (buff == NULL)
			return (null_error("malloc failed"));
		final_cmd = ft_strjoin(buff, cmdarg, 0);
		if (final_cmd == NULL)
			return (null_error("malloc failed"));
		if (access(final_cmd, R_OK) == 0)
		{
			free(buff);
			return (final_cmd);
		}
		free(buff);
		free(final_cmd);
		i++;
	}
	return (0);
}

int	execute(t_data *data, char **cmd, char **envp)
{
	char	**paths;
	char	*final_cmd;
	int		line;

	line = ft_table_count((void **)(envp));
	paths = get_all_paths(envp, line);
	if (paths == NULL)
	{
		ft_chartable_free(paths);
		exit (127);
	}
	final_cmd = search_path(paths, cmd[0]);
	if (final_cmd == 0)
	{
		ft_tklstclear(&data->token_list, &free);
		clean_all(paths, cmd, final_cmd);
		perror("command not cucked");
		exit (127);
	}
	else
		execve(final_cmd, cmd, envp);
	clean_all(paths, cmd, final_cmd);
	ft_error("command not found");
	exit (g_exit);
}
