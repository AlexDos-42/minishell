/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeerror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:42:39 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/16 16:42:40 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*ispath(char *tmp, t_all *all)
{
	char	**path;
	int		i;
	char	*tab;

	i = 0;
	if ((path = ft_allpath(all)) != NULL)
	{
		while (path[i])
		{
			if (!ft_strncmp(tmp, path[i], ft_strlen(path[i])))
			{
				tab = ft_strdup(&tmp[ft_strlen(path[i]) + 1]);
				ft_freexec(path);
				free(tmp);
				return (tab);
			}
			i++;
		}
		ft_freexec(path);
	}
	return (tmp);
}

int			ft_existpipe(t_all *all, char *tab, int i)
{
	DIR				*dir;
	struct dirent	*dp;
	char			**path;

	if ((path = ft_allpath(all)) != NULL)
	{
		while (path[++i])
		{
			dir = opendir(path[i]);
			while ((dp = readdir(dir)) != NULL)
				if (!ft_strncmp(tab, dp->d_name, ft_strlen(tab))
				&& ft_strlen(tab) == ft_strlen(dp->d_name))
				{
					ft_freexec(path);
					closedir(dir);
					return (1);
				}
			closedir(dir);
		}
		ft_freexec(path);
	}
	return (0);
}

void		istabpipe_suite4(char *tab, t_all *all)
{
	char		*tmp;
	char		*tmpp;
	char		**new;

	if (tab && tab[ft_strlen(tab) ? ft_strlen(tab) - 1 : 0] == '\n')
	{
		tmpp = ft_substr(tab, 0, ft_strlen(tab) - 1);
		tmp = ft_strtrimslash(tmpp, " ");
		free(tmpp);
	}
	else
		tmp = ft_strtrimslash(tab, " ");
	new = ft_splitspace(tmp, ' ');
	free(tmp);
	tmp = new[0] ? ft_strdup(new[0]) : ft_strdup("");
	tmp = ft_suprguy(tmp);
	if (isexec(tmp))
		return (free(tmp));
	tmp = ispath(tmp, all);
	if (!ft_existpipe(all, tmp, -1) && tmp && tmp[0])
		ft_printf("minishell: %s: command not found\n", tmp);
	free(tmp);
	ft_freexec(new);
}

void		ispipe_again(char *tmp, int i, int j, char *tab)
{
	tmp = ft_substr(tab, i + 6, j);
	ft_printf("minishell: unset: « %s »");
	ft_printf("%s: identifiant non valable\n", tmp);
	free(tmp);
}

void		istabpipe_suite3(char *tab, t_all *all, int i)
{
	int			j;
	int			k;
	char		*tmp;

	tmp = 0;
	if (!ft_strncmp(&tab[i], "unset ", 6))
	{
		while (tab[i + 6])
		{
			k = 0;
			j = -1;
			while (tab[i + 6] == ' ')
				i++;
			while (tab[i + 6 + ++j] && tab[i + 6 + j] != ' ')
				if (tab[i + 6 + j] == '=')
					k = 1;
			if (k == 1)
				ispipe_again(tmp, i, j, tab);
			i += j;
		}
	}
	else
		istabpipe_suite4(&tab[i], all);
}
