/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:13:59 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 18:14:00 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

char	*ft_newtab(char *tab, char *env)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 1;
	while (tab[i] != '$')
		i++;
	while (tab[i + j] && tab[i + j] != ' ' && tab[i + j] != '\n' &&
		tab[i + j] != '\"' && tab[i + j] != '\'' && tab[i + j] != '\\' && tab[i + j] != '$')
		j++;
	if (i || env)
		new = ft_substr(tab, 0, i);
	if (env)
		new = ft_strjoin(new, env, 1);
	new = ft_strjoin(new, &tab[i + j], 1);
	free(tab);
	if (env)
		free(env);
	return (new);
}

char	*ft_isinenv(char *tab, t_all *all)
{
	int		k;
	int		i;
	char	*env;

	k = 0;
	while (all->env[k])
	{
		i = 0;
		while (all->env[k][i] && all->env[k][i] == tab[i + 1])
			i++;
		if (all->env[k][i] == '=' && (tab[i + 1] != '\0' || tab[i + 1] == ' '))
		{
			env = ft_substr(all->env[k], i + 1,
				ft_strlen(all->env[k]) - (i + 1));
			return (env);
		}
		k++;
	}
	env = NULL;
	return (env);
}

char	*ft_ret(char *tab)
{
	char	*new;
	int		i;
	char	*c_ret;

	i = 0;
	while (tab[i] != '$')
		i++;
	new = ft_substr(tab, 0, i);
	c_ret = ft_itoa(ret);
	new = ft_strjoin(new, c_ret, 1);
	free(c_ret);
	if (tab[i + 2])
		new = ft_strjoin(new, &tab[i + 2], 1);
	free(tab);
	return (new);
}

char	*ft_replace(char *tab, t_all *all)
{
	int		i;
	int		j;
	char	*env;

	i = -1;
	j = -1;
	while (tab[++i])
	{
		if (tab[i] == '\'' && !isguillemet(i, tab))
		{
			i++;
			while (tab[i])
			{
				j = 0;
				while(tab[i + j] && tab[i + j] == '\\')
					j++;
				if (tab[i + j] == '\'' && j % 2 == 0)
					break;
				i += tab[i + j + 1] ? j + 1 : j;
			}
		}
		j = 0;
		while(tab[i + j] && tab[i + j] == '\\')
			j++;
		i += j;
		if (tab[i + 1] && tab[i] == '$' && tab[i + 1] != ' ' && tab[i + 1] != '\n' && j % 2 == 0)
		{
			if (tab[i + 1] == '?')
			{
				tab = ft_ret(tab);
				i = -1;
			}
			else
			{
				env = ft_isinenv(&tab[i], all);
				if (!(tab = ft_newtab(tab, env)))
					return (NULL);
				i = -1;
			}
		}
	}
	return (tab);
}
