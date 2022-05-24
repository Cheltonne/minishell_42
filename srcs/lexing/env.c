/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaslan <phaslan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:40:45 by phaslan           #+#    #+#             */
/*   Updated: 2022/05/24 11:25:55 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*set_name(char *envp)
{
	char	*name;
	size_t	i;
	size_t	x;

	x = -1;
	i = 0;
	name = NULL;
	if (!envp || envp[0] == '=')
		return (NULL);
	while (envp[++x])
		if (envp[x] == '=')
			break ;
	if (envp[x] != '=')
		return (NULL);
	name = (char *)malloc(sizeof(char) + (x + 1));
	if (!name)
		return (NULL);
	while (i < x)
	{
		name[i] = envp[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*set_value(char *envp)
{
	char	*value;
	size_t	x;
	size_t	i;

	x = 0;
	i = 0;
	while (envp[x] && envp[x] != '=')
		x++;
	if (envp[x++] != '=')
		return (NULL);
	value = (char *)malloc(sizeof(char) * (ft_strlen(envp) - x + 1));
	if (!value)
		return (NULL);
	while (envp[x])
		value[i++] = envp[x++];
	value[i] = '\0';
	return (value);
}

char	**dupenv(t_envlist *env)
{
	int			i;
	char		**ret;
	char		*str;
	t_envlist	*copy;

	i = 0;
	copy = env;
	if (!copy)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_envlstsize(env) + 1));
	if (!ret)
		return (NULL);
	while (copy->name != NULL)
	{
		str = ft_strjoin(copy->name, copy->value, 0);
		copy = copy->next;
		ret[i] = ft_strdup(str);
		free(str);
		str = NULL;
		i++;
	}
	ret[i] = NULL;
	copy = env;
	return (ret);
}

void	dual_free(void **ptr, void **ptr2)
{
	free((*ptr));
	free((*ptr2));
}

t_envlist	*setup_env(char **envp)
{
	char		*name;
	char		*value;
	int			i;
	t_envlist	*ret;

	i = 0;
	name = NULL;
	value = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i])
	{
		name = set_name(envp[i]);
		if (name == NULL)
			return (NULL);
		value = set_value(envp[i]);
		if (value == NULL)
			return (NULL);
		(void)(((i == 0) && (ret = ft_envlstnew(name, value))) ||\
		(ft_envlstadd_back(&ret, ft_envlstnew(name, value))));
		i++;
	}
	ft_envlstadd_back(&ret, ft_envlstnew(NULL, NULL));
	return (ret);
}
