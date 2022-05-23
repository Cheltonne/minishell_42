/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paslan <paslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:50:45 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/21 14:30:42 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <signal.h>

void  	signalc(int signal) // dans cat, un ctrl c fait 2 sauts de lignes
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	setup_signal(void) // rajoute ca
{
	signal(SIGINT, &signalc);
	struct sigaction	sigquit_act;

	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
	return (0);
}
