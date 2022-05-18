/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paslan <paslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:40:45 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/18 20:12:18 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// tant que je trouve pas de fleche, j'incremente
// si je trouve une fleche, je vais aller check si c un simple ou double
// si c pas un simple ou un double, erreur
// si c un double je vais le transformer en double array
// si c un simple on continue
// une fois que c bon je vais vérifier les tokens autours
// si jamais le token dans sa direction inverse n'est pas un litt
// fail
// si jamais le token suivant est END
// fail
// si jamais 
// jpeux pas utiliser exit, va falloir que je fasse attention a comment sortir de mes fonctions

t_tklist	*arrow_ncheck(t_tklist *tk)
{
	while (tk->type != END)
	{
		if (tk->type == R_REDIR || tk->type == L_REDIR)
		{
			if (ft_strlen(tk->value) > 2)
			{
				g_exit = 2;
				if (tk->type == R_REDIR)
                    ft_putstr_fd("bash:syntax error near token '>>'\n", 2);
                if (tk->type == L_REDIR)
                    ft_putstr_fd("bash:syntax error near token '<<'\n", 2);
                return (NULL);
            }
		}
		tk = tk->next;
	}
    while (tk->prev != NULL)
        tk = tk->prev;
    //ft_putstr_fd("juste avant de rendre check_arrown\n", 2);
    return (tk);
}


int arrow_analyse(t_tklist *data)
{
    t_tklist *tk;

    tk = data;
    if (tk->next->type == END)
    {
        ft_putstr_fd("bash:parse error near token '\\n'\n", 2);
        return (2);
    }
    else if (tk->type == R_REDIR)
    {
        while (tk->prev != NULL)
        {
           tk = tk->next;
           if (tk->type != WHITESPACE)
                break;
        }
        if (tk->type != LITTERAL)
        {
            ft_putstr_fd("bash:parse error near token '>\n'", 2);
            return (2);
        }
    }
    else if (tk->type == L_REDIR)
    {
        while (tk->next->type != END)
        {
           tk = tk->next;
           if (tk->type != WHITESPACE)
                break;
        }
        if (tk->type != LITTERAL)
        {
            ft_putstr_fd("bash:parse error near token <\n", 2);
            return (2);
        }
    }
    return (0);
}


t_tklist *redir_scan(t_data *data)
{
	t_tklist	*tk;

	tk = data->token_list;
    // ft_putstr_fd("avant arrow arrange", 2);
    tk = arrow_ncheck(tk);
    if (tk == NULL)
        return(NULL);
    // ft_putstr_fd("post arrow arrange\n", 2);
	while (tk->type != END)
	{
	    if (tk->type == R_REDIR || tk->type == L_REDIR)
        {
            g_exit = arrow_analyse(tk);
            if (g_exit == 2)
                return (NULL);
            // ft_putstr_fd("\ncheck d'arrow\n", 2);
            if (ft_strlen(tk->value) == 2)
            {
                if (tk->type == R_REDIR)
                    tk->type = APPEND;
                else if (tk->type == L_REDIR)
                    tk->type = HERE_DOC;
            }
        }
        tk = tk->next;
	}
    while (tk->prev != NULL)
        tk = tk->prev;
    // ft_putstr_fd("fin de redir scan\n", 2);
    return(tk);
}
