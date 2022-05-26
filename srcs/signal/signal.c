/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:50:45 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/26 12:51:26 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <signal.h>

extern int	g_exit;

void	signalc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 130;
	}
}

void	sig_fork(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_exit = 130;
	}
}

void	sig_quit(int sig)
{
	struct sigaction	sigquit_act;

	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_DFL;
	if (sig == SIGQUIT)
		ft_putstr_fd("quit (core dumped)\n", 2);
}

int	setup_signal(void)
{
	struct sigaction	sigquit_act;

	signal(SIGINT, &signalc);
	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
	return (0);
}

void	dual_signals(void)
{
	signal(SIGINT, &sig_fork);
	signal(SIGQUIT, &sig_quit);
}
