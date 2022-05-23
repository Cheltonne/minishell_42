/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:26:27 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 19:23:26 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0 
# define SUCCESS 1
# define FAILURE 0 
# define WRITE 1
# define READ 0
# define CHILD 0
# define COLOR_ORANGE "\1\033[38;5;208m\2"
# define COLOR_RESET "\1\x1b[0m\2"
# define PS1 "minishell de ses Morts\1💀💀󠁩󠁲>󠀱󠀶󠁿\2 "

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>

extern int	g_exit;

typedef enum e_type
{
	LITTERAL,
	WHITESPACE,
	S_QUOTE,
	D_QUOTE,
	L_REDIR,
	R_REDIR,
	HERE_DOC,
	APPEND,
	PIPE,
	DOLLAR,
	EXIT_STATUS,
	END
}						t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
}				t_token;

typedef struct s_tklist
{
	t_type			type;
	char			*value;
	struct s_tklist	*next;
	struct s_tklist	*prev;
}				t_tklist;

typedef struct s_envlist
{
	char				*name;
	char				*value;
	struct s_envlist	*next;
	struct s_envlist	*prev;
}				t_envlist;

typedef struct s_cmd
{
	char	**cmd;
	int		in;
	int		out;
	pid_t	id;
}				t_cmd;

typedef struct s_data
{
	t_envlist		*env;
	char			**env_arr;
	t_tklist		*token_list;
	char			*line;
	t_cmd			**cmds;
	int				pipe_nb;
}				t_data;

t_tklist	*lexer(char *line);
int			ft_table_count(void **file);
int			sp_char_nb(t_tklist *tokens, t_type type);
t_tklist	*second_scan(t_data *data);
t_cmd		*cmd_builder(t_tklist **head);
void		cmd_builder_norm(t_tklist **head, t_cmd **ret, int *i);
int			clean_all(char **paths, char **cmdarg, char *final);
char		*search_path(char **paths, char *cmdarg);
char		**get_all_paths(char **enpv, int line);
int			execute(char **cmd, char **envp);
int			exec_single_cmd(t_data *data);
void		exit_error(char *error_msg);
int			pipe_count(t_tklist *token_list);
int			setup_signal(void);
t_tklist	*ft_tklstnew(t_type type, char *value);
t_tklist	*ft_tklstlast(t_tklist *lst);
int			ft_tklstsize(t_tklist *lst);
int			ft_tklstadd_back(t_tklist **alst, t_tklist *new);
void		ft_envlstadd_back(t_envlist **alst, t_envlist *new);
int			set_data(t_data *data, char **envp);
char		**dupenv(t_envlist *env);
t_envlist	*setup_env(char **envp);
t_envlist	*ft_envlstnew(char *name, char *value);
int			ft_envlstsize(t_envlist *lst);
void		expand(t_data *data);
void		del_node(t_envlist *node);
void		del_tknode(t_tklist *node);
t_envlist	*ft_envlstlast(t_envlist *lst);
t_tklist	*join_litterals(t_data *data);
int			only_whitespaces(char *str);
void		expand(t_data *data);
int			good_expand(char *s1, char *s2);
int			unset_cmd(t_data *data, t_cmd *command);
int			export_cmd(t_data *data, t_cmd *command);
int			env_cmd(t_data *data);
int			cd_cmd(t_data *data, t_cmd *command);
int			exec_builtin(t_data *data, t_cmd *command);
int			is_builtin(char **cmd);
int			echo_cmd(t_cmd *command, t_data *data);
int			try_pwd(t_data *data);
char		*set_name(char *envp);
char		*set_value(char *envp);
int			not_valid_env_arg(char *arg, int x);
int			ft_strcmp(const char *s1, const char *s2);
char		*get_venv(t_envlist *env, char *name);
int			fork_pipes(int n, t_data *data);
int			spawn_proc(int in, int out, int fd[2], t_data *data, t_cmd *command);
void		fork_wrapper(pid_t *child);
void		redir_anal(t_tklist **head, t_cmd **ret, int *i);
int			left_redirection(t_cmd **ret, t_tklist ***head);
int			right_redirection(t_cmd **ret, t_tklist ***head);
int			append(t_cmd **ret, t_tklist ***head);
int			here_doc(t_cmd **ret, t_tklist ***head);
t_tklist	*suppr_quotes(t_data *data);
t_tklist	*join_litt(t_data *data);
void		query_user(char *limiter, int *buf_fd);
t_tklist	*redir_scan(t_data *data);
t_tklist	*suppr_quotes(t_data *data);
t_tklist	*join_litt(t_data *data);
int			exit_cmd(t_data *data, t_cmd *command);
void		verify_main_args(int argc, char** argv, char **envp);
void		wait_wrapper(t_data *data);
void		temp_free(t_data *data);
void		free_everything(t_data *data);
int			ad(int *value);
void		free_dual_token_arr(t_token **tokens, int tokens_len);
void		ft_tklstclear(t_tklist **lst, void (*del)(void*));
int			parent_signal(void);
void		sig_fork(int sig);
void		heredoc_sighandler(int sig);
void		signal_heredoc(int signal);
void		free_env(t_envlist *lst);


#endif
