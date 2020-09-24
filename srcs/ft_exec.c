/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:56:51 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:56:53 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			is_exec(char *tmp, char *tab)
{
	if ((ft_strncmp(tmp, "./", 2) && tmp[2] != ' ') &&
	ft_strncmp(tmp, "sh", 2) && ft_strncmp(tmp, "../", 3)
	&& ft_strncmp(tmp, "/", 1))
	{
		ft_printf("minishell: %s: command not found\n", tab);
		free(tmp);
		ret = 127;
	}
	return (1);
}

int			isexec(char *tab)
{
	int				j;
	char			*tmp;
	char			*new;

	new = ft_strdup(tab);
	tmp = ft_strtrim(new, " ");
	free(new);
	tmp = ft_suprguy(tmp);
	j = ft_strlen(tmp) - 1;
	if (j > 0)
	{
		if (tmp[j] == 'h' && tmp[j - 1] == 's' && tmp[j - 2] == '.')
		{
			is_exec(tmp, tab);
		}
	}
	free(tmp);
	return (0);
}

char		**ft_allpath(t_all *all)
{
	char			*tmp;
	char			**path;
	int				i;

	i = 0;
	path = NULL;
	while (all->env[i])
	{
		if (!ft_strncmp(all->env[i], "PATH", 4))
		{
			tmp = ft_strdup(&all->env[i][5]);
			path = ft_split(tmp, ':');
			free(tmp);
			break ;
		}
		i++;
	}
	return (path);
}

void		ft_freexec(char **tab)
{
	int				i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char		*ft_exist(t_all *all, char *tab, int i)
{
	DIR				*dir;
	struct dirent	*dp;
	char			**path;
	char			*tmp;

	if ((path = ft_allpath(all)) != NULL)
	{
		while (path[++i])
			if ((dir = opendir(path[i])) != NULL)
			{
				while ((dp = readdir(dir)) != NULL)
					if (!ft_strncmp(tab, dp->d_name, ft_strlen(tab))
					&& ft_strlen(tab) == ft_strlen(dp->d_name))
					{
						tmp = ft_strjoin(path[i], "/", 0);
						tab = ft_strjoin(tmp, tab, 1);
						ft_freexec(path);
						closedir(dir);
						return (tab);
					}
				closedir(dir);
			}
		ft_freexec(path);
	}
	return (NULL);
}
