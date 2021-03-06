/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:04:10 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 17:48:44 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit;

int	mini_exit(t_data *data)
{
	ft_putstr_fd("\nexit", 2);
	free_everything(data);
	exit(g_exit % 255);
	return (0);
}

int	only_whitespaces(char *str)
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
	data->cmds = ft_calloc(sizeof(t_cmd), 1);
	if (data->cmds == NULL)
		return (FAILURE);
	data->token_list = lexer(buf);
	free(buf);
	if (data->token_list == NULL)
		return (FAILURE);
	data->token_list = second_scan(data);
	if (data->token_list == NULL)
		exit_error("Error.😱😱😱\n");
	expand(data);
	data->token_list = join_litterals(data);
	data->token_list = suppr_quotes(data);
	data->token_list = join_litt(data);
	data->pipe_nb = pipe_count(data->token_list);
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

	verify_main_args(argc, argv, envp);
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (1);
	data->env = setup_env(envp);
	data->env_arr = dupenv(data->env);
	g_exit = 0;
	while (1)
	{
		setup_signal();
		data->line = readline(COLOR_ORANGE PS1 COLOR_RESET);
		if (data->line && *data->line != '\0' && only_whitespaces(data->line) \
		== FALSE)
		{
			if (handle_input(data, envp) == FAILURE)
				break ;
		}
		else if (data->line == NULL)
			mini_exit(data);
		temp_free(data);
	}
	return (0);
}
