/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:04:10 by chajax            #+#    #+#             */
/*   Updated: 2022/05/25 01:25:23 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit;

int	mini_exit(t_data *data)
{
	ft_putstr_fd("exit\n", 2);
	free_everything(data);
	exit(g_exit % 255);
	return (0);
}

int	only_wh(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

int	set_data(t_data *data, char **envp)
{
	char	*buf;

	buf = ft_strjoin(data->line, " ", 0);
	data->token_list = lexer(buf);
	free(buf);
	data->cmds = NULL;
	if (data->token_list == NULL)
		return (FAILURE);
	data->token_list = second_scan(data);
	if (data->token_list == NULL)
		exit_error("Error.😱😱😱\n", data);
	data->token_list = expand(data);
	data->token_list = join_litterals(data);
	data->token_list = suppr_quotes(data);
	data->token_list = join_litt(data);
	data->pipe_nb = pipe_count(data->token_list);
	data->cmds = ft_calloc(sizeof(t_cmd), data->pipe_nb + 1);
	if (data->cmds == NULL)
		return (FAILURE);
	return (SUCCESS);
	(void)envp;
}

int	handle_input(t_data *data, char **envp)
{
	int	i;

	i = 0;
	add_history(data->line);
	if (set_data(data, envp) == FAILURE)
		return (FAILURE);
	data->token_list = redir_scan(data);
	if (data->token_list == NULL)
		return (SUCCESS);
	while (i < data->pipe_nb + 1)
		data->cmds[i++] = cmd_builder(&data->token_list);
	if (data->cmds == NULL)
		return (FAILURE);
	if (data->pipe_nb == 0)
		exec_single_cmd(data);
	else
		fork_pipes(data->pipe_nb + 1, data);
	wait_wrapper(data);
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	verify_main_args(argc, argv);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (1);
	init_env(data, envp);
	while (1)
	{
		setup_signal();
		data->line = readline(COLOR_ORANGE PS1 COLOR_RESET);
		if (data->line && *data->line != '\0' && only_wh(data->line) == FALSE)
		{
			if (handle_input(data, envp) == FAILURE)
			{
				temp_free(data);
				continue ;
			}
		}
		else if (data->line == NULL)
			mini_exit(data);
		temp_free(data);
	}
	free_everything(data);
	return (0);
}
