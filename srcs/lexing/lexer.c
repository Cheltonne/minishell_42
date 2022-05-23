/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:33:11 by chajax            #+#    #+#             */
/*   Updated: 2022/05/23 14:15:20 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_builder(enum e_type type, char *value)
{
	t_token	*ret;

	ret = ft_calloc(1, sizeof(t_token));
	ret->type = type;
	ret->value = ft_strdup(value);
	free(value);
	return (ret);
}

t_token	*char_anal(char c)
{
	char	*value;

	value = ft_calloc(2, 1);
	ft_memset(value, c, 1);
	ft_memset(value + 1, 0, 1);
	if (c == '\'')
		return (token_builder(S_QUOTE, value));
	else if (c == '\"')
		return (token_builder(D_QUOTE, value));
	else if (c == '<')
		return (token_builder(L_REDIR, value));
	else if (c == '>')
		return (token_builder(R_REDIR, value));
	else if (c == '|')
		return (token_builder(PIPE, value));
	else if (c == '$')
		return (token_builder(DOLLAR, value));
	else if (c == ' ')
		return (token_builder(WHITESPACE, value));
	else
		return (token_builder(LITTERAL, value));
}

t_tklist	*f_token_builder(t_token **tokens, int tokens_len)
{
	int			i;
	int			o;
	t_tklist	*ret;
	char		*f_value;

	i = -1;
	o = 0;
	f_value = ft_strdup(tokens[0]->value);
	while (++i < tokens_len - 1)
	{
		if (tokens[i]->type == tokens[i + 1]->type && tokens[i]->type != S_QUOTE
			&& tokens[i]->type != D_QUOTE)
			f_value = ft_strjoin(f_value, tokens[i + 1]->value, 1);
		else
		{
			(void)(((o == 0) && (ret = ft_tklstnew(tokens[i]->type, f_value)))\
			|| ft_tklstadd_back(&ret, ft_tklstnew(tokens[i]->type, f_value)));
			(void)((!(f_value = ft_strdup(tokens[i + 1]->value)) || (ad(&o))));
		}
	}
	ft_tklstadd_back(&ret, ft_tklstnew(END, NULL));
	free(f_value);
	free_dual_token_arr(tokens, tokens_len);
	return (ret);
}

t_tklist	*lexer(char *line)
{
	t_token	**token;
	int		y;
	size_t	i;

	y = 0;
	i = 0;
	token = ft_calloc(ft_strlen(line), sizeof(t_token *));
	if (!token)
		return (NULL);
	while (line[i])
	{
		token[y] = char_anal(line[i]);
		y++;
		i++;
	}
	return (f_token_builder(token, ft_strlen(line)));
}
