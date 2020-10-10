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

char	*put_guy_env(char *env)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	i = 0;
	while (env[i])
	{
		if (env[i] == ' ')
		{
			while (env[i] && env[i] == ' ')
				i++;
			if (env[i])
				j+= 2;
		}
		else
			i++;
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(env) + 3 + j);
	i = 0;
	j = 0;
	tmp[j++] = '\"';
	while (env[i])
	{
		if (env[i] == ' ')
		{
			tmp[j++] = '\"';
			while (env[i] && env[i] == ' ')
				tmp[j++] = env[i++];
			tmp[j++] = '\"';
		}
		else
			tmp[j++] = env[i++];
	}
	tmp[j++] = '\"';
	tmp[j++] = '\0';
	free(env);
	return (tmp);
}

char	*ft_newtab(char *tab, char *env, int i)
{
	int		j;
	char	*new;

	if (env)
		env = put_guy_env(env);
	j = 1;
	while (tab[i + j] && tab[i + j] != ' ' && tab[i + j] != '\n' &&
		tab[i + j] != '\"' && tab[i + j] != '\'' && tab[i + j] != '\\'
		&& tab[i + j] != '$' && tab[i + j] != ',' && tab[i + j] != '@'
		&& tab[i + j] != '|' && tab[i + j] != '/')
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

char	*put_slash(char *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (env[++i])
		if (env[i] == '\"')
			j++;
	tmp = ft_calloc(sizeof(char), ft_strlen(env) + j + 1);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (env[i] == '\"')
			tmp[j++] = '\\';
		tmp[j++] = env[i++];
	}
	tmp[j] = '\0';
	free(env);
	return (tmp);
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
		if (all->env[k][i] == '=')
		{
			if ((tab[i + 1] < 48 || (tab[i + 1] > 57 && tab[i + 1] < 65)
			|| (tab[i + 1] > 90 && tab[i + 1] < 97) || tab[i + 1] > 122)
			&& tab[i + 1] != '_')
			{
				env = ft_substr(all->env[k], i + 1,
				ft_strlen(all->env[k]) - (i + 1));
				return (env = put_slash(env));
			}
		}
		k++;
	}
	env = NULL;
	return (env);
}

int		ft_isitnot(char *tab, int i)
{
	if (tab[i + 1] != '$' && tab[i + 1] != ';' && tab[i + 1]
			!= '\\' && tab[i + 1] != ':' && tab[i + 1] != '%' && tab[i + 1]
			!= '\'' && tab[i + 1] != '\"')
		return (1);
	return (0);
}

int		simple_quote(char *tab, int i, int j)
{
	j = 0;
	if (tab[i] == '\'' && !isguillemet(i, tab))
		while (tab[i + ++j] && tab[i + j] != '\'')
			;
	return (j);
}

int		is_after_redir(char *tab, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (i - j > 0 && tab[i - ++j])
	{
		if (tab[i - j] == ' ')
			;
		else if (tab[i - j] == '>')
		{
			j = 0;
			while (tab[i + j] && tab[i + j] != ' ' && tab[i + j] != ';'
			&& tab[i + j] != '<' && tab[i + j] != '>' && tab[i + j] != '|'
			&& tab[i + j] != '\n')
				j++;
			tmp = ft_substr(tab, i, j);
			ft_printf("minishell: %s : redirection ambiguë\n", tmp);
			free(tab);
			free(tmp);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

char	*ft_replace(char *tab, t_all *all, int i, int j)
{
	char	*env;

	while (tab && tab[++i])
	{
		j = simple_quote(tab, i, j);
		i += (tab[i + j] == '\'') ? j : 0;
		j = 0;
		while (tab[i + j] && tab[i + j] == '\\')
			j++;
		i += j;
		if (tab[i + 1] && tab[i] == '$' && tab[i + 1] != ' ' &&
		tab[i + 1] != '\n' && j % 2 == 0 && isguillemet(i, tab) != 2)
		{
			if (tab[i + 1] == '?')
				tab = ft_ret(tab, i--);
			else if (ft_isitnot(tab, i))
			{
				env = ft_isinenv(&tab[i], all);
				if (env == NULL && is_after_redir(tab, i))
					return (NULL);
				if (!(tab = ft_newtab(tab, env, i--)))
					return (NULL);
			}
		}
	}
	return (tab);
}
