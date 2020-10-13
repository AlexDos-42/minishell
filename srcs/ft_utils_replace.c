/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:57:49 by edouvier          #+#    #+#             */
/*   Updated: 2020/10/13 14:57:52 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*put_guy_env_bis(char *env, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] == ' ')
		tmp[j++] = env[i++];
	if (env[i])
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

char	*put_guy_env(char *env)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	i = 0;
	while (env[i] == ' ')
		i++;
	while (env[i])
	{
		if (env[i] == ' ')
		{
			while (env[i] && env[i] == ' ')
				i++;
			if (env[i])
				j += 2;
		}
		else
			i++;
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(env) + 3 + j);
	return (put_guy_env_bis(env, tmp));
}

char	*ft_newtab(char *tab, char *env, int i)
{
	int		j;
	char	*new;

	if (env)
		env = put_guy_env(env);
	j = 1;
	if ((tab[i + j] > 47 && tab[i + j] < 58))
		j++;
	else
		while (tab[i + j] && tab[i + j] != ' ' && tab[i + j] != '\n' &&
			tab[i + j] != '\"' && tab[i + j] != '\'' && tab[i + j] != '\\'
			&& tab[i + j] != '$' && tab[i + j] != ',' && tab[i + j] != '@'
			&& tab[i + j] != '|' && tab[i + j] != '/' && tab[i + j] != '=')
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
