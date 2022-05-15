/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:05:50 by phaslan           #+#    #+#             */
/*   Updated: 2022/04/19 15:49:16 by phaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    check_opt(char *args)
{
    int    i;

    i = 2;
    if (args && (args[0] == '-' && args[1] == 'n'))
    {
        while (args[i] == 'n')
            i++;
        if (args[i] == '\0')
            return (1);
    }
    return (0);
}

int    echo_cmd(char **args)
{
    int    i;
    int    option;

    i = 0;
    option = 0;
    /*
    int x = 0;
     printf("====test====\n");
    while (args[x])
    {
    printf("%s\n", args[x]);
    x++;
    }
     printf("======\n"); */
    // case echo
    if (!args[1])
    {
        ft_putstr_fd("\n", 1);
        return (0);
    }
    // case echo -n 
    if (check_opt(args[1]) && !args[2])
        return (0);
    // je check si le -n existe
    while (check_opt(args[++i]))
        option++;
    // je dump la string entiere et un petit espace entre chaque mot
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        i++;
        if (args[i])
            ft_putstr_fd(" ", 1);
    }
    // si j'ai pas de de -n je balance la newline
    if (!option)
        ft_putstr_fd("\n", 1);
    return (0);
}