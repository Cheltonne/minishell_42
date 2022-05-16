/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paslan <paslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:04:10 by chajax            #+#    #+#             */
/*   Updated: 2022/05/16 16:45:00 by paslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_exit;

int	only_whitespaces(char *str)
{
	int i;

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
	data->here_doc = 0;
	data->pipe_nb = pipe_count(data->line);
	data->cmds = ft_calloc(sizeof(t_cmd), 1);
	if (data->cmds == NULL)
		return (FAILURE);
	data->token_list = lexer(ft_strjoin(data->line, " ")); //free line; beware of double free
	if (data->token_list == NULL)
		return (FAILURE);
	data->token_list = second_scan(data);
	if (data->token_list == NULL)
		exit_error("Error.😱😱😱\n");
	expand(data);
	data->token_list = join_litterals(data);
	data->token_list = suppr_quotes(data);
	data->token_list = join_litt(data);
	return (SUCCESS);
	(void)envp;
}

int	handle_input(t_data *data, char **envp)
{
	int i;

	i = 0;
	if (ft_strncmp(data->line, "exit", 4) == 0)
		exit(EXIT_SUCCESS);
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
	i = 0;
	while (i < data->pipe_nb + 1)
	{
		if (is_builtin(data->cmds[i]->cmd))
			g_exit = exec_builtin(data, data->cmds[i]->cmd);
		else if (data->pipe_nb == 0)
			exec_single_cmd(data);
		else
		{
			fork_pipes(data->pipe_nb + 1, data);
			break;
		}
		i++;
	}
	waitpid(data->id, &g_exit, 0);
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	return (SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		exit_error("minishell does not accept any arguments 😰😱😨😰😥😓\n");
	setup_signal();
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (1);
	data->env = setup_env(envp);
	data->env_arr = dupenv(data->env);
	g_exit = 0;
	while (1)
	{
		data->line = readline("jcrois jsuis amsomniaque o_O >");
		if (data->line && *data->line != '\0' && only_whitespaces(data->line) == FALSE)
		{
			if (handle_input(data, envp) == FAILURE)
				break ;
		}
		else if (data->line == NULL)
			printf("\n");
		free(data->line);
	}
	return (0);
}
