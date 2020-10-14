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
			if ((dir = opendir(path[i])) != NULL)
			{
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
		}
		ft_freexec(path);
	}
	return (0);
}

void		istabpipe_suite4(char **new, t_all *all)
{
	char		*tmp;

	tmp = new[0] ? ft_strdup(new[0]) : ft_strdup("");
	if (isexec(tmp))
		return (free(tmp));
	tmp = ispath(tmp, all);
	if (!ft_existpipe(all, tmp, -1) && tmp && tmp[0])
	{
		if (g_pipe != 2)
			ft_printf("minishell: %s: command not found\n", tmp);
		g_quit = 1;
	}
	free(tmp);
}

void		ispipe_again(char **new, char *tmp)
{
	int			i;
	int			j;

	i = 0;
	while (new[++i])
	{
		new[i] = ft_suprguy(new[i]);
		if ((new[i][0] > 47 && new[i][0] < 58) || new[i][0] == '=')
		{
			if (g_pipe != 2)
				ft_printf("%s `%s': not a valid identifier\n", tmp, new[i]);
			g_quit = 1;
		}
		else if ((j = -1) == -1)
			while (new[i][++j])
				if (new[i][j] < 48 || (new[i][j] > 58 && new[i][j] < 65)
				|| (new[i][j] > 90 && new[i][j] < 97) || new[i][j] > 122)
				{
					if (g_pipe != 2)
						ft_printf("%s `%s': not a valid identifier\n",
						tmp, new[i]);
					g_quit = 1;
					break ;
				}
	}
}

void		istabpipe_suite3(char **new, t_all *all, int i)
{
	if (!ft_strncmp(new[0], "unset", 5) && !new[0][i + 5])
	{
		if (new[1])
			ispipe_again(new, "minishell: unset:");
	}
	else
		istabpipe_suite4(new, all);
}
