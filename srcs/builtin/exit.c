/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paslan <paslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:38 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/17 18:21:53 by paslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define LLMAX_D10 922337203685477580

void	free_env(t_envlist *lst)
{
	t_envlist	*tmp;

	if (lst)
	{
		while (!ft_strcmp(lst->value, "END"))
		{
			tmp = lst->next;
            del_node(lst);
			lst = tmp;
		}
	}
}

void    free_tokens(t_tklist *lst)
{
    t_tklist	*tmp;

	if (lst)
	{
		while (lst->type != END)
		{
			tmp = lst->next;
            del_tknode(lst);
			lst = tmp;
        }
	}
}

int	ft_atoll_err(char *str, long long int *nbr)
{
	int					neg;
	unsigned long long int	abs;

	if (!*str)
		return (1);
	neg = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	abs = 0;
	while (*str == '0')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (abs >= LLMAX_D10 && (abs > LLMAX_D10 || *str > ('7' + neg)))
			return (1);
		abs *= 10;
		abs += *str - '0';
		str++;
	}
	if (*str)
		return (1);
	*nbr = abs;
	if (neg)
		*nbr = -abs;
	return (0);
}

int	ft_strdigit(char *str)
{
	long long int	status;

	status = -1;
	if (ft_atoll_err(str, &status))
		{
            ft_putstr_fd("exit:error", 2);
            return(1);
        }
	status &= 255ULL;
	return ((int)status);
}

int exit_cmd(t_data *data, char **args)
{
    // il faut que je check si on est dans un subprocess ou pas déjà
    // si oui, je fais rien ? je kill le child ?
    // si non, j'exit le process en entier t'as compris
    // ouais je dois juste pas quitter le truc en entier SI exit est après une pipe
    
    // si jamais il y a trop d'arguments (2) je ferme
    if (data->id != 0)
        ft_putstr_fd("exit\n", 2);
    if (args[1] && args[2])
    {
        ft_putstr_fd("exit:too many arguments", 2);
        return (1);
    }
    // sinon je free la struct data en entier
    // je clear les liste chainées 
    // rl_clear_history
    // si il n'y a qu'un arg je vais is_strdigit pour être sur que c un arg valide
    // j'exit avec le status du child
    else
    {
        clear_history();
        free_env(data->env);
        free_tokens(data->token_list);
        ft_putstr_fd("exit", 2);
        if (args[1] != NULL)
			g_exit = ft_strdigit(args[1]);
		ft_chartable_free(data->env_arr);
        
		exit(g_exit);
        // il faut que je code le truc qui va permettre de free
        // la structure data
        // que je code un truc qui va free token list
        // le truc qui va free env list
        // normalement c bon c les 3 trucs principaux a free
        // je vais juste d'abord faire une fonction qui va free toute la table
    }
    // exit(g_exit);
    //return(0);
}